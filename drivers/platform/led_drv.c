#include <linux/module.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/sched.h>
#include <linux/pm.h>
#include <linux/sysctl.h>
#include <linux/proc_fs.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/input.h>
#include <linux/irq.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/errno.h>
#include <linux/ioport.h>

static int major;
static struct class *class;
static volatile unsigned long *gpn_con;
static volatile unsigned long *gpn_dat;
static int pin;

static int led_open(struct inode *inode, struct file *filp)
{
	*gpn_con &= ~(0x3 << pin);
	*gpn_con |= (0x1 << pin);

	return 0;
}

static ssize_t led_write(struct file *filp, const char __user *buf, 
			size_t count, loff_t *ppos)
{
	int val;

	copy_from_user(&val, buf, count);

	if (val == 1) {
		*gpn_dat &= ~(1<<pin);
	} else {
		*gpn_dat |= (1<<pin);
	}

	return 0;
}

static struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.open = led_open,
	.write = led_write,
};

static int led_probe(struct platform_device *pdev)
{
	struct resource *res;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	gpn_con = ioremap(res->start, res->end - res->start  + 1);
	gpn_dat = gpn_con + 1;

	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	pin = res->start;

	major = register_chrdev(0, "myled", &led_fops);
	
	class = class_create(THIS_MODULE, "myled");
	if (IS_ERR(class)) {
		printk(KERN_ALERT "class err\n");
		return -1;
	}

	device_create(class, NULL, MKDEV(major, 0), NULL, "led");
	
	printk(KERN_ALERT "find her\n");	

	return 0;
}

static int led_remove(struct platform_device *pdev)
{
	device_destroy(class, MKDEV(major, 0));
	class_destroy(class);
	unregister_chrdev(major, "myled");
	iounmap(gpn_con);

	return 0;
}

struct platform_driver led_drv = {
	.probe  = led_probe,
	.remove = led_remove,
	.driver = {
		.name  = "myled",
	},
};

static int led_drv_init(void)
{
	platform_driver_register(&led_drv);

	return 0;
}

static __exit void led_drv_exit(void)
{
	platform_driver_unregister(&led_drv);
}

module_init(led_drv_init);
module_exit(led_drv_exit);
MODULE_LICENSE("GPL");

