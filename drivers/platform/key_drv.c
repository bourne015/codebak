#include <linux/module.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
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

//#define S3C_EINT(x) ((x) + 64 + 5 + 32)
//#define IRQ_EINT(x) S3C_EINT(x)

static int major;
static struct class *class;
static volatile unsigned long *gpm_con;
static volatile unsigned long *gpm_dat;
//static volatile unsigned long *gpn_con;
//static volatile unsigned long *gpn_dat;

static struct file_operations key_fops = {
	.owner = THIS_MODULE,
	//.write = led_write,
};

static int led_init(void)
{
	*gpm_con &= ~(0xffff);
	*gpm_con |= (0x1111);

	return 0;
}

static unsigned int dat = 0x0;
static int count = 0;
static irqreturn_t key_irq(int irq, void *dev_id)
{
	dat = ~dat;
	*gpm_dat = dat;
	printk(KERN_ALERT "irq hit: %d\n", count++);

	return IRQ_HANDLED;
}

struct resource *res;
static int key_probe(struct platform_device *pdev)
{
	int i;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	gpm_con = ioremap(res->start, res->end - res->start  + 1);
	gpm_dat = gpm_con + 1;

	led_init();

	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (res == NULL)
		printk("no irq resource\n");
	for (i = 0; i < 6; i++) {
		request_irq(res->start + i, key_irq,
				IRQ_TYPE_EDGE_BOTH, "key", NULL);
        }

	major = register_chrdev(0, "mykey", &key_fops);
	
	class = class_create(THIS_MODULE, "mykey");
	if (IS_ERR(class)) {
		printk(KERN_ALERT "class err\n");
		return -1;
	}

	device_create(class, NULL, MKDEV(major, 0), NULL, "mykey");

	return 0;
}

static int key_remove(struct platform_device *pdev)
{
	int i;

        for (i = 0; i < 6; i++) {
                free_irq(res->start + i, NULL);
        }

	device_destroy(class, MKDEV(major, 0));
	class_destroy(class);
	unregister_chrdev(major, "mykey");
	iounmap(gpm_con);

	return 0;
}

struct platform_driver key_drv = {
	.probe  = key_probe,
	.remove = key_remove,
	.driver = {
		.name  = "mykey",
	},
};

static int key_drv_init(void)
{
	return platform_driver_register(&key_drv);
}

static __exit void key_drv_exit(void)
{
	platform_driver_unregister(&key_drv);
}

module_init(key_drv_init);
module_exit(key_drv_exit);
MODULE_LICENSE("GPL");

