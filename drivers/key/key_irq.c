#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
//#include <linux/types.h>
//#include <linux/errno.h>
//#include <linux/slab.h>
#include <linux/device.h>
#include <linux/sched.h>
//#include <linux/poll.h>
#include <linux/interrupt.h>
//#include <linux/wait.h>
#include <linux/irq.h>

//#include <asm/io.h>
//#include <asm/irq.h>
#include <asm/system.h>
//#include <asm/uaccess.h>

//#include <mach/map.h>
//#include <mach/regs-gpio.h>
//#include <mach/gpio-bank-n.h>
//#include <mach/gpio-bank-m.h>

static int key_major = 251;
struct cdev cdev;
struct class *myclass;

static DECLARE_WAIT_QUEUE_HEAD(key_waitq);

static volatile int ev_press = 0;

struct key_irq_desc {
        int irq;
        int number;
        char *name;
};

struct key_irq_desc key_irqs[] = {
        {IRQ_EINT(0), 0, "KEY0"},
        {IRQ_EINT(1), 1, "KEY1"},
        {IRQ_EINT(2), 2, "KEY2"},
        {IRQ_EINT(3), 3, "KEY3"},
        {IRQ_EINT(4), 4, "KEY4"},
        {IRQ_EINT(5), 5, "KEY5"},
};

static irqreturn_t key_handle(int irq, void *dev_id)
{
	ev_press = 1;
	wake_up_interruptible(&key_waitq);
	printk(KERN_ALERT "hit\n");

	return IRQ_HANDLED;
}

static int key_open(struct inode *inode, struct file *filp)
{
	int i;

	printk(KERN_ALERT "opened in kernel\n\n\n");
	for (i = 0; i < 1; i++) {
                request_irq(key_irqs[i].irq, key_handle, IRQ_TYPE_EDGE_BOTH,
				key_irqs[i].name, (void *)&key_irqs[i]);
        }

//	ev_press = 1;
        return 0;
}

static int 
key_read(struct file *filp, char *buff, size_t count, loff_t *offp)
{
	if (!ev_press) {
                        wait_event_interruptible(key_waitq, ev_press);
        }
	
//	copy_to_user(buff, &ev_press, count);
	printk(KERN_ALERT "read done in kernel:%d\n\n", ev_press);
        ev_press = 0;
	
	return 0;
}

static int key_release(struct inode *inode, struct file *filp)
{
	int i;

	for (i = 0; i < 1; i++) {
                free_irq(key_irqs[i].irq, (void *)&key_irqs[i]);
        }

        return 0;
}

static const struct file_operations key_fops = {
        .owner	= THIS_MODULE,
        .open   = key_open,
        .read   = key_read,
//        .write  = key_write,
//      .poll   = key_poll,
        .release = key_release,
};

void key_setup(struct cdev dev, int index)
{
        int err, devno = MKDEV(key_major, index);

        cdev_init(&dev, &key_fops);
        dev.owner = THIS_MODULE;
        err = cdev_add(&dev, devno, 1);
        if (err)
                printk(KERN_NOTICE "ERROR %d adding mem %d", err, index);
}

static int __init dev_init(void)
{
//	int ret;
/*

	if (key_major)
		ret = register_chrdev_region(devno, 1, "key");
	else {
		ret = alloc_chrdev_region(&devno, 0, 1, "key");
		key_major = MAJOR(devno);
	}
	if (ret < 0)
		return ret;

	key_setup(cdev, 0);
*/
	key_major = register_chrdev(0, "key", &key_fops);
	myclass = class_create(THIS_MODULE, "dev_key");
        device_create(myclass, NULL,  MKDEV(key_major, 0), NULL, "key");

	return 0;
}

static void __exit dev_exit(void)
{
	cdev_del(&cdev);
	device_destroy(myclass, MKDEV(key_major, 0));
	class_destroy(myclass);
	unregister_chrdev_region(MKDEV(key_major, 0), 1);
}

module_init(dev_init);
module_exit(dev_exit);
MODULE_LICENSE("GPL");
