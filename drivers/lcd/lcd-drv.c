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

#define S3CFB_HFP               2       /* front porch */
#define S3CFB_HSW               41      /* hsync width */
#define S3CFB_HBP               2       /* back porch */

#define S3CFB_VFP               2       /* front porch */
#define S3CFB_VSW               10      /* vsync width */
#define S3CFB_VBP               2       /* back porch */

#define S3CFB_HRES              480     /* horizon pixel  x resolition */
#define S3CFB_VRES              272     /* line cnt       y resolution */

#define S3CFB_HRES_VIRTUAL      480     /* horizon pixel  x resolition */
#define S3CFB_VRES_VIRTUAL      544     /* line cnt       y resolution */  //Do not  change 544 to 272 .I think that 272 is right in the driver of LCD4.3,but double frambuffer 
// in multimediatest do not use if change 544 to 272

#define S3CFB_HRES_OSD          480     /* horizon pixel  x resolition */
#define S3CFB_VRES_OSD          272     /* line cnt       y resolution */

#define S3CFB_VFRAME_FREQ       60      /* frame rate freq */
#define S3CFB_PIXEL_CLOCK       (S3CFB_VFRAME_FREQ * (S3CFB_HFP + S3CFB_HSW +\
                                S3CFB_HBP + S3CFB_HRES) * (S3CFB_VFP +\
                                S3CFB_VSW + S3CFB_VBP + S3CFB_VRES))


struct fb_info *fbinfo;

static volatile unsigned long *gpecon;
static volatile unsigned long *gpedat;
static volatile unsigned long *gpfcon;
static volatile unsigned long *gpfdat;
static volatile unsigned long *gpicon;
static volatile unsigned long *gpjcon;
static volatile unsigned long *mifpcon;
static volatile unsigned long *spcon;
static unsigned long pseudo_palette[16];
static struct s3c_lcd_regs {
	volatile unsigned long vidcon0; 
	volatile unsigned long vidcon1;
	volatile unsigned long vidcon2;
	volatile unsigned long reserved1;
	volatile unsigned long vidtcon0;
	volatile unsigned long vidtcon1;
	volatile unsigned long vidtcon2;
	volatile unsigned long reserved2;
	volatile unsigned long wincon0;
	volatile unsigned long wincon1;
	volatile unsigned long wincon2;
	volatile unsigned long wincon3;
	volatile unsigned long wincon4; //030
	volatile unsigned long reserved3[3];
	volatile unsigned long vidosd0a; //040
	volatile unsigned long vidosd0b;
	volatile unsigned long vidosd0c; //048
	volatile unsigned long reserved4[4*5+1];
	volatile unsigned long vidw00add0b0; //0a0
	volatile unsigned long reserved5[4*3-1];
	volatile unsigned long vidw00add1b0; //0d0
	volatile unsigned long reserved6[4*3-1];
	volatile unsigned long vidw00add2;   //100
};
struct s3c_lcd_regs *lcd_regs;
/*
static lcd_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	var->red = info.red;
	var->green = info.green;
	var->blue = info.blue;
}
*/
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

static struct fb_ops s3c_fb_ops = {
	.owner		= THIS_MODULE,
	//.fn_check_var   = lcd_check_var
	.fb_setcolreg	= s3c_fb_setcolreg,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
};

static void s3cfb_init(void)
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

	mifpcon = ioremap(0x7410800c, 4);
        *mifpcon &= ~(1<<3);

        spcon = ioremap(0x7f0081a0, 4);
        *spcon  &= ~(0x3);
        *spcon  |= 0x1;

        lcd_regs->vidcon0 &= ~((0x3<<26) | (0x3<<17) | (0xff<<6) | (0x3<<2));
        lcd_regs->vidcon0 |= (2<<6) | (1<<4) | (0x3);
        lcd_regs->vidcon1 |= ((0x1 << 5) | (3 << 6));
        lcd_regs->vidcon1 &= ~(0x1 << 7);

        lcd_regs->vidtcon0 = ((1 << 16) | (1 << 8) | (9 << 0));
        lcd_regs->vidtcon1 = ((1 << 16) | (1 << 8) | (40 << 0));
        lcd_regs->vidtcon2 = ((479 << 0) | (271 << 11));

        lcd_regs->wincon0 = (0xb << 2);

        lcd_regs->vidosd0a = (0<<11) | (0 << 0);
        lcd_regs->vidosd0b = ((479)<<11) | ((271) << 0);
        lcd_regs->vidosd0c = ((271 + 1) * (479 + 1)) & 0xffffff;
/*
        lcd_regs->vidw00add0b0 = fbinfo->fix.smem_start;
        lcd_regs->vidw00add1b0 = (fbinfo->fix.smem_start +
                        fbinfo->fix.smem_len) & (0xffffff);
*/
        lcd_regs->vidw00add2 = 480*4;

 	/*lcd on*/
        *gpedat |= (1<<0);

        /*backlight enable*/
        *gpfdat |= (1<<14);

        /*display on*/
        lcd_regs->vidcon0 |= 0x3;
        lcd_regs->wincon0 |= 1;
}

static void s3cfb_info_set(void)
{
	strcpy(fbinfo->fix.id, "mylcd");
        fbinfo->fix.smem_len            = 480*272*32/8;
        fbinfo->fix.type                = FB_TYPE_PACKED_PIXELS;

        fbinfo->fix.type_aux            = 0;
        fbinfo->fix.xpanstep            = 0;
        fbinfo->fix.ypanstep            = 1;
        fbinfo->fix.ywrapstep           = 0;
//      fbinfo->fix.mmio_len            = 0;

        fbinfo->fix.visual              = FB_VISUAL_TRUECOLOR;
        fbinfo->fix.accel               = FB_ACCEL_NONE;
        fbinfo->fix.line_length         = 480*4;

        fbinfo->var.xres                = 480;
        fbinfo->var.yres                = 272;
        fbinfo->var.xres_virtual        = 480;
        fbinfo->var.yres_virtual        = 272; //544
//      fbinfo->var.xoffset             = 0;
//      fbinfo->var.yoffset             = 0;
        fbinfo->var.bits_per_pixel      = 32;
//      fbinfo->var.grayscale           = 32;

        fbinfo->var.red.offset          = 16;
        fbinfo->var.red.length          = 8;
        fbinfo->var.green.offset        = 8;
        fbinfo->var.green.length        = 8;
        fbinfo->var.blue.offset         = 0;
        fbinfo->var.blue.length         = 8;
        fbinfo->var.transp.offset       = 0;
        fbinfo->var.transp.length       = 0;
        fbinfo->var.nonstd              = 0;
        fbinfo->var.activate            = FB_ACTIVATE_NOW;
//      fbinfo->var.hight               = 0;
//      fbinfo->var.width               = 0;
        fbinfo->var.accel_flags         = 0;

        fbinfo->var.pixclock            = S3CFB_PIXEL_CLOCK;
        fbinfo->var.left_margin         = 2;
        fbinfo->var.right_margin        = 2;
        fbinfo->var.upper_margin        = 2;
        fbinfo->var.lower_margin        = 2;
        fbinfo->var.hsync_len           = 41;
        fbinfo->var.vsync_len           = 10;
//      fbinfo->var.sync                = 0;
        fbinfo->var.vmode               = FB_VMODE_NONINTERLACED;
//      fbinfo->var.rotate              = 0;
        fbinfo->fbops                   = &s3c_fb_ops;

        fbinfo->screen_size             = 480*272*32/8;
        fbinfo->pseudo_palette          = pseudo_palette;
}

static int s3c_lcd_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct clk *lcd_clk;
	int size;
	
	fbinfo = framebuffer_alloc(0, &pdev->dev);
	if (!fbinfo) {
		printk(KERN_ERR "mem err");
		return -ENOMEM;
	}
	platform_set_drvdata(pdev, fbinfo);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	size = res->end - res->start + 1;
	request_mem_region(res->start, size, "s3c-lcd");
	lcd_regs = ioremap(res->start, size);	

	lcd_clk = clk_get(NULL, "lcd");
	if (!lcd_clk) {
		printk(KERN_ALERT "failed to get lcd clk\n");
		return -1;
	}
	clk_enable(lcd_clk);

	s3cfb_init();
	s3cfb_info_set();
	
	fbinfo->screen_base = dma_alloc_writecombine(NULL, fbinfo->fix.smem_len,
                                 &fbinfo->fix.smem_start, GFP_KERNEL);
        lcd_regs->vidw00add0b0 = fbinfo->fix.smem_start;
        lcd_regs->vidw00add1b0 = (fbinfo->fix.smem_start +
                        fbinfo->fix.smem_len) & (0xffffff);
	register_framebuffer(fbinfo);
}

static int s3c_lcd_remove(struct platform_device *pdev)
{
	iounmap(lcd_regs);
	unregister_framebuffer(fbinfo);

	return 0;
}

static struct platform_driver s3c_lcd_drv = {
	.probe = s3c_lcd_probe,
	.remove = s3c_lcd_remove,
	.driver = {
		.name = "ok6410-lcd",
		.owner = THIS_MODULE,
	},
};

static int __init s3c_lcd_init(void)
{
	return platform_driver_register(&s3c_lcd_drv);
}

static void __exit s3c_lcd_exit(void)
{
	platform_driver_unregister(&s3c_lcd_drv);
}

module_init(s3c_lcd_init);
module_exit(s3c_lcd_exit);
MODULE_LICENSE("GPL");
