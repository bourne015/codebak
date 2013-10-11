#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/list.h>
#include <linux/timer.h>
#include <linux/serial_core.h>
#include <linux/platform_device.h>

static struct resource led_resource[] = {
	[0] = { //led gpm
		.start = 0x7F008820, 
		.end   = 0x7F008820 + 8,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		//key gpn
		.start = 0x7f008830,
		.end   = 0x7f008830 + 8,
		.flags = IORESOURCE_MEM,
	},
	[2] = {//key0-5
        	.start = IRQ_EINT(0),
        	.end   = IRQ_EINT(5),
        	.flags = IORESOURCE_IRQ,
	}
};

static void led_release(struct device *dev)
{
	return;
}

static struct platform_device led_dev = {
	.name 	  = "mykey",
	.id 	  = -1,
	.num_resources = ARRAY_SIZE(led_resource),
	.resource = led_resource,
	.dev	  = { 
    		.release = led_release, 
	},
};

static __init int led_dev_init(void)
{
	platform_device_register(&led_dev);
	return 0;
}

static __exit void led_dev_exit(void)
{
	platform_device_unregister(&led_dev);
}

module_init(led_dev_init);
module_exit(led_dev_exit);
MODULE_LICENSE("GPL");

