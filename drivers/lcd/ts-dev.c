#include <linux/kernel.h>
#include <linux/platform_device.h>

#include <mach/map.h>
#include <mach/irqs.h>
#include <plat/devs.h>
#include <plat/cpu.h>
#include <mach/ts.h>

#define S3C_TS_BASE 0x7e00b000

#define S3C_IRQ_OFFSET	(32)
#define S3C_IRQ(x)	((x) + S3C_IRQ_OFFSET)
#define IRQ_VIC1_BASE	S3C_IRQ(32)
#define S3C64XX_IRQ_VIC1(x) (IRQ_VIC1_BASE + (x))

#define S3C_IRQ_ADC	S3C64XX_IRQ_VIC1(31)
#define S3C_IRQ_PENDN	S3C64XX_IRQ_VIC1(30)


/* Touch srcreen */
static struct resource s3c_ts_resource[] = {
	[0] = {
		.start = S3C_TS_BASE,
		.end   = S3C_TS_BASE + SZ_256 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = S3C_IRQ_PENDN,
		.end   = S3C_IRQ_PENDN,
		.flags = IORESOURCE_IRQ,
	},
	[2] = {
		.start = S3C_IRQ_ADC,
		.end   = S3C_IRQ_ADC,
		.flags = IORESOURCE_IRQ,
	}
};

struct platform_device s3c_dev_ts = {
	.name		  = "ok6410-ts",
	.id		  = -1,
	.num_resources	  = ARRAY_SIZE(s3c_ts_resource),
	.resource	  = s3c_ts_resource,
};

static  __init int s3c_dev_init(void)
{
	return platform_device_register(&s3c_dev_ts);
}

static  __exit void s3c_dev_exit(void)
{
	platform_device_unregister(&s3c_dev_ts);
}

module_init(s3c_dev_init);
module_exit(s3c_dev_exit);
MODULE_LICENSE("GPL");
//EXPORT_SYMBOL(s3c_ts_set_platdata);
