#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/ioport.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/system.h>
#include <linux/cdev.h>

#include"led_def.h"

#define gpio 0x7f008820
#define ioaddr addr
#define led_count 1
#define LED_MAJOR 252
int led_major = LED_MAJOR;

struct cdev cdev;

/*
unsigned long gpmcon = gpcon;
unsigned long gpmdat = gpdat;
unsigned long gpmpud = gppud;
*/
unsigned long addr;
struct resource led_re = {
	.start = gpio,
	.end = gpio + 0xc,
	.name = "ledname",
	.flags = IORESOURCE_MEM,
};

static void led_ioinit(void)
{
	//int ret;
	request_mem_region(led_re.start,led_re.end-led_re.start,"ledname");
	addr = (unsigned long)ioremap(led_re.start, led_re.end - led_re.start);
	//gpmcon = 0x0;
	printk(KERN_ALERT "at first addr=%lu   ioaddr=%lu\n",addr,ioaddr);
	iowrite32(0x111111, ioaddr);
	iowrite32(0xf7, ioaddr + 0x04);
}

static void led_release(void)
{
	iounmap(addr);
	release_mem_region(led_re.start, led_re.end - led_re.start);
}

static int let_stat(void)
{
	int ret;
	//gpmcon = 0x0;
	iowrite32(0x00, ioaddr);
	printk(KERN_ALERT "in stat,addr=%lu   ioaddr=%lu\n",addr,ioaddr);
	ret = ioread32(ioaddr + 0x04);
	return ret;
}

static int led_set(char ioarg)
{
//	int ret;
	//gpmcon = 0x111111;
	printk(KERN_ALERT "in set,addr=%lu   ioaddr=%lu\n",addr,ioaddr);
	printk(KERN_ALERT "user send %c to kernel\n",ioarg);
	iowrite32(0x111111, ioaddr);
	if (ioarg == '0')
		iowrite32(0x00, addr + 0x4);
	else if (ioarg == '1')
		iowrite32(0x0f, addr + 0x4);
	return 0;
}

static long led_ioctl(struct file *filp, unsigned int cmd, 
			unsigned long arg)
{
	int ioarg, ret = 0;
	if (_IOC_TYPE(cmd) != MEM_IOC_MAGIC) return -ENOTTY;
	if (_IOC_NR(cmd) > MEM_IOC_MAXNR) return -ENOTTY;

	switch(cmd) {
		case MEM_IOCSTAT:
			ioarg = let_stat();
			ret = put_user(ioarg, (int *)arg);
			break;
		case MEM_IOCSET:
			ret = get_user(ioarg, (int *)arg);
			led_set(ioarg);
			break;
		default:
			return -EINVAL;
	}
	return ret;
}

struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = led_ioctl,
};

int __init led_init(void)
{
	int ret = 0;
	dev_t devno;
//	register_chrdev(0, "ledname", &led_fops);//it too old

/*alloc the device number*/
	if (led_major) {
		devno = MKDEV(led_major, 0);
		ret = register_chrdev_region(devno, led_count, "ledname");
	} else {
		ret = alloc_chrdev_region(&devno, 0, led_count, "ledname");
		led_major = MAJOR(devno);
	}
	
	if (ret < 0) {
		printk(KERN_ALERT "can't get major %d\n", led_major);
		return ret;
	}
/*register the device,,,,init*/	
	cdev_init(&cdev, &led_fops);
	cdev.owner = THIS_MODULE;
	cdev.ops = &led_fops;
	cdev_add(&cdev, MKDEV(led_major, 0), led_count);

/*init the i/o stat*/
	led_ioinit();

	return ret;
}

void led_exit(void)
{
	led_release();
	unregister_chrdev_region(MKDEV(led_major, 0), led_count);
	cdev_dev(&cdev);
}

module_init(led_init);
module_exit(led_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("FANTAO");
