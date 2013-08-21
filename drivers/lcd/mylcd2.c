#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/fb.h>
#include <linux/init.h>
#include <linux/dma-mapping.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/wait.h>
#include <linux/platform_device.h>
#include <linux/clk.h>

#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/div64.h>

#include <asm/mach/map.h>

#define S3CFB_HFP		2	/* front porch */
#define S3CFB_HSW		41	/* hsync width */
#define S3CFB_HBP		2	/* back porch */

#define S3CFB_VFP		2	/* front porch */
#define S3CFB_VSW		10	/* vsync width */
#define S3CFB_VBP		2	/* back porch */

#define S3CFB_HRES		480	/* horizon pixel  x resolition */
#define S3CFB_VRES		272	/* line cnt       y resolution */

#define S3CFB_HRES_VIRTUAL	480	/* horizon pixel  x resolition */
#define S3CFB_VRES_VIRTUAL	544	/* line cnt       y resolution */  //Do not  change 544 to 272 .I think that 272 is right in the driver of LCD4.3,but double frambuffer 
// in multimediatest do not use if change 544 to 272

#define S3CFB_HRES_OSD		480	/* horizon pixel  x resolition */
#define S3CFB_VRES_OSD		272	/* line cnt       y resolution */

#define S3CFB_VFRAME_FREQ     	60	/* frame rate freq */
#define S3CFB_PIXEL_CLOCK	(S3CFB_VFRAME_FREQ * (S3CFB_HFP + S3CFB_HSW +\
				S3CFB_HBP + S3CFB_HRES) * (S3CFB_VFP +\
				S3CFB_VSW + S3CFB_VBP + S3CFB_VRES))
static struct fb_info *fbinfo;
static unsigned long pseudo_palette[16];
static volatile unsigned long *gpfcon;
static volatile unsigned long *gpfdat;
static volatile unsigned long *gpecon;
static volatile unsigned long *gpedat;
static volatile unsigned long *gpicon;
static volatile unsigned long *gpjcon;
static volatile unsigned long *MIFPCON;
static volatile unsigned long *SPCON;
#define  s3c_lcd_ba	0x77100000
#define  vidcon0	0x000
#define  vidcon1	0x004
#define  vidtcon0	0x010
#define  vidtcon1	0x014
#define  vidtcon2	0x018
#define  wincon0	0x020
#define  vidosd0a	0x040
#define  vidosd0b	0x044
#define  vidosd0c	0x048
#define  vidw00add0b0	0x0a0
#define  vidw00add1b0	0x0d0
#define  vidw00add2	0x100

static int s3c_fb_setcolreg(unsigned int regno, unsigned int red,
			     unsigned int green, unsigned int blue,
			     unsigned int transp, struct fb_info *info)
{
	unsigned long color = 0;
	unsigned long *p;

	red   = (red >> (16 - info->var.red.length)) << info->var.red.offset;
	green = (green>>(16-info->var.green.length)) << info->var.green.offset;
	blue  = (blue >> (16-info->var.blue.length)) << info->var.blue.offset;
	color = red | green | blue;

	p = info->pseudo_palette;
	p[regno] = color; 

	return 0;
}

static struct fb_ops fb_ops = {
	.owner		= THIS_MODULE,
	.fb_setcolreg	= s3c_fb_setcolreg,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
};

static void fb_gpio_set(void)
{
	gpicon = ioremap(0x7F008100, 8);
	gpjcon = ioremap(0x7F008120, 8);
	gpecon = ioremap(0x7F008080, 8);
	gpedat = gpecon + 1;
	gpfcon = ioremap(0x7F0080A0, 8);
	gpfdat = gpfcon + 1;

	*gpicon = 0xaaaaaaaa;
	*gpjcon = 0xaaaaaaaa;   

	*gpfcon &= ~(0x3<<28);
	*gpfcon |=  (1<<28); 
	*gpecon &= ~(0xf);
	*gpecon |= (0x1);

}
static void fb_init_register(void)
{
	struct clk *clk;
	int hclk, clkval;

	MIFPCON = ioremap(0x7410800C, 4);
	*MIFPCON &= ~(1<<3);

	SPCON = ioremap(0x7F0081A0, 4);
	*SPCON  &= ~(0x3);
	*SPCON  |= 0x1;

	clk = clk_get(NULL, "lcd");
	clk_enable(clk);
	clk = clk_get(NULL, "hclk");
	hclk = clk_get_rate(clk);
	clkval = hclk/9000000 - 1;	

	VIDCON0 = ioremap(0x77100000, 4);
	*VIDCON0 &= ~((0x3<<26) | (0x3<<17) | (0xff<<6) | (0x3<<2));
        *VIDCON0 |= (clkval<<6) | (1<<4) | (0x3);

	VIDCON1 = ioremap(0x77100004, 4);
	*VIDCON1 |= ((0x1 << 5) | (3 << 6));
        *VIDCON1 &= ~(0x1 << 7);

	VIDTCON0 = ioremap(0x77100010, 4);
	*VIDTCON0 = ((1 << 16) | (1 << 8) | (9 << 0));

	VIDTCON1 = ioremap(0x77100014, 4);
	*VIDTCON1 = ((1 << 16) | (1 << 8) | (40 << 0));

	VIDTCON2 = ioremap(0x77100018, 4);
	*VIDTCON2 = ((479 << 0) | (271 << 11));

	WINCON0 = ioremap(0x77100020, 4);
	*WINCON0 = (0xb << 2);

	VIDOSD0A = ioremap(0x77100040, 4);
	*VIDOSD0A = (0<<11) | (0 << 0);

	VIDOSD0B = ioremap(0x77100044, 4);
	*VIDOSD0B = ((479)<<11) | ((271) << 0);

	VIDOSD0C = ioremap(0x77100048, 4);
	*VIDOSD0C = ((271 + 1) * (479 + 1)) & 0xffffff;
/*
	VIDW00ADD1B0 = ioremap(0x771000D0, 4);
	VIDW00ADD0B0 = ioremap(0x771000A0, 4);
	*VIDW00ADD0B0 = fbinfo->fix.smem_start;
	*VIDW00ADD1B0 = (fbinfo->fix.smem_start +
			fbinfo->fix.smem_len) & (0xffffff);
*/
	VIDW00ADD2 = ioremap(0x77100100, 4);
	*VIDW00ADD2 = 480*4;

	/*display off*/
	*VIDCON0 &= ~(0x3);
	*WINCON0 &= ~1;

	/*lcd on*/
	*gpedat |= (1<<0);

	/*backlight enable*/
	*gpfdat |= (1<<14);

	/*display on*/
	*VIDCON0 |= 0x3;
	*WINCON0 |= 1;
}

static void fb_params_set(void)
{
	strcpy(fbinfo->fix.id, "mylcd");
	//fbinfo->fix.smem_start		= 0x58000000;
	fbinfo->fix.smem_len		= 480*272*32/8;	
	fbinfo->fix.type		= FB_TYPE_PACKED_PIXELS;

	fbinfo->fix.type_aux		= 0;
	fbinfo->fix.xpanstep		= 0;
	fbinfo->fix.ypanstep		= 1;
	fbinfo->fix.ywrapstep		= 0;
//	fbinfo->fix.mmio_len		= 0;

	fbinfo->fix.visual   		= FB_VISUAL_TRUECOLOR;
	fbinfo->fix.accel		= FB_ACCEL_NONE;
	fbinfo->fix.line_length		= 480*4;

	fbinfo->var.xres		= 480;
	fbinfo->var.yres		= 272;
	fbinfo->var.xres_virtual	= 480;
	fbinfo->var.yres_virtual	= 272; //544
//	fbinfo->var.xoffset		= 0;
//	fbinfo->var.yoffset		= 0;
	fbinfo->var.bits_per_pixel	= 32;
//	fbinfo->var.grayscale		= 32;
	
	fbinfo->var.red.offset  	= 16;
	fbinfo->var.red.length     	= 8;
	fbinfo->var.green.offset   	= 8;
	fbinfo->var.green.length   	= 8;
	fbinfo->var.blue.offset    	= 0;
	fbinfo->var.blue.length    	= 8;
	fbinfo->var.transp.offset    	= 0;
	fbinfo->var.transp.length    	= 0;
	fbinfo->var.nonstd		= 0;
	fbinfo->var.activate		= FB_ACTIVATE_NOW;
//	fbinfo->var.hight	     	= 0;
//	fbinfo->var.width	     	= 0;
	fbinfo->var.accel_flags     	= 0;
	
	fbinfo->var.pixclock     	= S3CFB_PIXEL_CLOCK;
	fbinfo->var.left_margin     	= 2;
	fbinfo->var.right_margin     	= 2;
	fbinfo->var.upper_margin     	= 2;
	fbinfo->var.lower_margin     	= 2;
	fbinfo->var.hsync_len     	= 41;
	fbinfo->var.vsync_len     	= 10;
//	fbinfo->var.sync     		= 0;
	fbinfo->var.vmode		= FB_VMODE_NONINTERLACED;
//	fbinfo->var.rotate     		= 0;
	fbinfo->fbops              	= &fb_ops;

	fbinfo->screen_size   		= 480*272*32/8;

	fbinfo->pseudo_palette 		= pseudo_palette;
}

static int __init lcd_init(void)
{
	fbinfo = framebuffer_alloc(0, NULL);
	if (!fbinfo)
		return -ENOMEM;

	fb_gpio_set();
	fb_init_register();
	fb_params_set();

	fbinfo->screen_base = dma_alloc_writecombine(NULL, fbinfo->screen_size,
				 &fbinfo->fix.smem_start, GFP_KERNEL);

        VIDW00ADD1B0 = ioremap(0x771000D0, 4);
        VIDW00ADD0B0 = ioremap(0x771000A0, 4);
        *VIDW00ADD0B0 = fbinfo->fix.smem_start;
        *VIDW00ADD1B0 = (fbinfo->fix.smem_start +
                        fbinfo->fix.smem_len) & (0xffffff);

	register_framebuffer(fbinfo);

	return 0;
}

static void __exit lcd_exit(void)
{
	unregister_framebuffer(fbinfo);

	dma_free_writecombine(NULL, fbinfo->fix.smem_len,
			fbinfo->screen_base, fbinfo->fix.smem_start);
	iounmap(gpfcon);
	iounmap(gpecon);
	iounmap(gpicon);
	iounmap(gpjcon);

	iounmap(MIFPCON);
	iounmap(SPCON);
	iounmap(VIDCON0);
	iounmap(VIDCON1);
	iounmap(VIDTCON0);
	iounmap(VIDTCON1);
	iounmap(VIDTCON2);
	iounmap(WINCON0);
	iounmap(VIDOSD0A);
	iounmap(VIDOSD0B);
	iounmap(VIDOSD0C);
	iounmap(VIDW00ADD1B0);
	iounmap(VIDW00ADD2);

	framebuffer_release(fbinfo);
}

module_init(lcd_init);
module_exit(lcd_exit);
MODULE_LICENSE("GPL");
