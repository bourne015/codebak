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

struct fb_info *fbinfo;
static volatile unsigned long *gpbcon;
static volatile unsigned long *gpbdat;
static volatile unsigned long *gpfcon;
static volatile unsigned long *gpfdat;
static volatile unsigned long *gpecon;
static volatile unsigned long *gpedat;
static volatile unsigned long *gpicon;
static volatile unsigned long *gpjcon;
static u32 pseudo_palette[16];
static volatile unsigned long *MIFPCON;
static volatile unsigned long *SPCON;
static volatile unsigned long *VIDCON0;
static volatile unsigned long *VIDCON1;
static volatile unsigned long *VIDTCON0;
static volatile unsigned long *VIDTCON1;
static volatile unsigned long *VIDTCON2;
static volatile unsigned long *WINCON0;
static volatile unsigned long *VIDOSD0A;
static volatile unsigned long *VIDOSD0B;
static volatile unsigned long *VIDOSD0C;
static volatile unsigned long *VIDW00ADD0B0;
static volatile unsigned long *VIDW00ADD1B0;
static volatile unsigned long *VIDW00ADD2;

static inline unsigned int 
chan_to_field(unsigned int chan, struct fb_bitfield *bf)
{
	chan &= 0xffff;
	chan >>= 16 - bf->length;
	return chan << bf->offset;
}

static int s3c_fb_setcolreg(unsigned int regno, unsigned int red,
			     unsigned int green, unsigned int blue,
			     unsigned int transp, struct fb_info *info)
{
	unsigned int val;
	
	if (regno > 16)
		return 1;

	val  = chan_to_field(red, &info->var.red);
	val |= chan_to_field(green, &info->var.green);
	val |= chan_to_field(blue, &info->var.blue);
	
	//((u32 *)(info->pseudo_palette))[regno] = val;
	pseudo_palette[regno] = val;
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

	gpbcon = ioremap(0x7F008020, 8);
	gpbdat = gpbcon + 1;
//	*gpbcon &= ~(0xf << 24);
//	*gpbcon |= (0x1);

	*gpicon = 0xaaaaaaaa;
	*gpjcon = 0xaaaaaaaa;   
/*
	*gpfcon &= ~(0x3<<28);
	*gpfcon |=  (1<<28); 
	*gpecon &= ~(0xf);
	*gpecon |= (0x1);
*/
}
static void fb_init_register(void)
{
	struct clk *clk;
	int hclk;
	int clkval;

	MIFPCON = ioremap(0x7410800C, 4);
	*MIFPCON &= ~(1<<3);

	SPCON = ioremap(0x7F0081A0, 4);
	*SPCON  &= ~(0x3);
	*SPCON  |= 0x1;

	clk = clk_get(NULL, "lcd");
	clk_enable(clk);
	hclk = clk_get_rate(clk);
	clkval = hclk/9000000 - 1;
	
	VIDCON0 = ioremap(0x77100000, 4);
//	*VIDCON0 = ((1 << 2) | (4 << 6) | (1 << 17) | (0x11 << 20));
	*VIDCON0 = ((1<<4) | (clkval<<6) | (0<<17) | (0<<26) | (0<<29));


	VIDCON1 = ioremap(0x77100004, 4);
	*VIDCON1 = ((1 << 5) | (1 << 6) | (0 << 4) | (0 << 7));

	VIDTCON0 = ioremap(0x77100010, 4);
	*VIDTCON0 = ((1 << 16) | (1 << 8) | (9 << 0));

	VIDTCON1 = ioremap(0x77100014, 4);
	*VIDTCON1 = ((1 << 16) | (1 << 8) | (40 << 0));

	VIDTCON2 = ioremap(0x77100018, 4);
	*VIDTCON2 = ((479 << 0) | (271 << 11));

	WINCON0 = ioremap(0x77100020, 4);
	*WINCON0 = ((1 << 0) | (0xb << 2));

	VIDOSD0A = ioremap(0x77100040, 4);
	*VIDOSD0A = (0<<11) | (0 << 0);

	VIDOSD0B = ioremap(0x77100044, 4);
	*VIDOSD0B = ((479+1)<<11) | ((271+1) << 0);

	VIDOSD0C = ioremap(0x77100048, 4);
	*VIDOSD0C = (271 + 1) * (479 + 1);

	VIDW00ADD1B0 = ioremap(0x771000D0, 4);
	VIDW00ADD0B0 = ioremap(0x771000A0, 4);
//	*VIDW00ADD1B0 = (((479 + 1)*4 + 0) * (271 + 1)) & (0xffffff);
	*VIDW00ADD1B0 = (fbinfo->fix.smem_start +
			fbinfo->fix.smem_len) & (0xffffff);
	*VIDW00ADD0B0 = fbinfo->fix.smem_start;

	VIDW00ADD2 = ioremap(0x77100100, 4);
	*VIDW00ADD2 = 480;

	/*display off*/
	*VIDCON0 &= ~(0x3);
	*WINCON0 &= ~1;

	/*lcd on*/
//	*gpedat |= (1<<0);

	/*backlight enable*/
//	*gpfdat |= (1<<14);
//	*gpbdat |= (0x1);

	/*display on*/
	*VIDCON0 |= 0x3;
	*WINCON0 |= 1;

}

static void fb_params_set(void)
{
	strcpy(fbinfo->fix.id, "mylcd");
	fbinfo->fix.smem_len		= 480*272*32/8;	
	fbinfo->fix.type		= FB_TYPE_PACKED_PIXELS;
/*
	fbinfo->fix.type_aux		= 0;
	fbinfo->fix.xpanstep		= 0;
	fbinfo->fix.ypanstep		= 0;
	fbinfo->fix.ywrapstep		= 0;
*/
	fbinfo->fix.visual   = FB_VISUAL_TRUECOLOR;
//	fbinfo->fix.accel		= FB_ACCEL_NONE;
	fbinfo->fix.line_length		= 480*4;

	fbinfo->var.xres		= 480;
	fbinfo->var.yres		= 272;
	fbinfo->var.xres_virtual	= 480;
	fbinfo->var.yres_virtual	= 272;
//	fbinfo->var.xoffset		= 0;
//	fbinfo->var.yoffset		= 0;
	fbinfo->var.bits_per_pixel	= 32;
	fbinfo->var.red.offset  	= 16;
	fbinfo->var.red.length     	= 8;
	fbinfo->var.green.offset   	= 8;
	fbinfo->var.green.length   	= 8;
	fbinfo->var.blue.offset    	= 0;
	fbinfo->var.blue.length    	= 8;
//	fbinfo->var.nonstd		= 0;
	fbinfo->var.activate		= FB_ACTIVATE_NOW;
//	fbinfo->var.accel_flags     	= 0;
//	fbinfo->var.vmode		= FB_VMODE_NONINTERLACED;

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

	fbinfo->screen_base = dma_alloc_writecombine(NULL, fbinfo->fix.smem_len,
				 &fbinfo->fix.smem_start, GFP_KERNEL);
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
