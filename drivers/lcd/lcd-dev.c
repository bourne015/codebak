#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>

#define S3C_LCD_BA 0x77100000

static struct resource s3c_lcd_res[] = {
	[0] = {
		.start = S3C_LCD_BA,
		.end   = S3C_LCD_BA + SZ_16K -1,
		.flags = IORESOURCE_MEM, 
	},
};

static struct platform_device s3c_lcd_dev  = {
	.name = "ok6410-lcd",
	.id = -1,
	.resource = s3c_lcd_res,
	.num_resources = ARRAY_SIZE(s3c_lcd_res),
};

static int __init lcd_dev_init(void)
{
	return platform_device_register(&s3c_lcd_dev);
}

static void __exit lcd_dev_exit(void)
{
	platform_device_unregister(&s3c_lcd_dev);
}

module_init(lcd_dev_init);
module_exit(lcd_dev_exit);

MODULE_LICENSE("GPL");
