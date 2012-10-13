#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/irq.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/sched.h>

#include <mach/map.h>
#include <mach/regs-gpio.h>
#include <mach/gpio-bank-n.h>
#include <mach/gpio-bank-m.h>

#define DEV_NAME	"key_led"

static volatile char key_values[] = {'0', '0', '0', '0', '0', '0', '0', '0'};

static DECLARE_WAIT_QUEUE_HEAD(button_waitq);

static volatile int ev_press = 0;

struct button_irq_desc {
	int irq;
	int number;
	char *name;
};

struct button_irq_desc button_irqs[] = {
	{IRQ_EINT(0), 0, "KEY0"},
	{IRQ_EINT(1), 1, "KEY1"},
	{IRQ_EINT(2), 2, "KEY2"},
	{IRQ_EINT(3), 3, "KEY3"},
	{IRQ_EINT(4), 4, "KEY4"},
	{IRQ_EINT(5), 5, "KEY5"},
};

static int button_handle(int irq, void *dev_id)
{
	struct button_irq_desc *button_irqs = (struct button_irq_desc *)dev_id;
	int down;
	int number = button_irqs->number;
	unsigned tmp;

	switch (number) {
		case 0: case 1: case 2: case 3: case 4: case 5:
			tmp = readl(S3C64XX_GPMDAT);
			down = !(tmp & (1<<number));
			break;
		default:
			down = 0;
	}

	if (down != (key_values[number] & 1)) {
		key_values[number] = '0' + down;
		
		ev_press = 1;
		wake_up_interruptible(&button_waitq);
	}
	return IRQ_HANDLED;
}

int dev_open(struct inode *inode, struct file *file)
{
	int i, err = 0;

	for (i = 0; sizeof(button_irqs)/sizeof(button_irqs[1]); i++) {
		if (button_irqs[i].irq < 0)
			continue;
		err = request_irq(button_irqs[i].irq, button_handle,
				IRQ_TYPE_EDGE_BOTH, button_irqs[i].name,
				(void *)&button_irqs[i]);
		if (err)
			break;
	}
	if (err) {
		i--;
		for (; i >= 0; i--) {
			if (button_irqs[i].irq < 0)
				continue;
			disable_irq(button_irqs[i].irq);
			free_irq(button_irqs[i].irq, (void *)&button_irqs[i]);
		}
		return -EBUSY;
	}
	ev_press = 1;
	return 0;	
}

int dev_read(struct file *filp, char *buff,
		size_t count, loff_t *offp)
{
	unsigned long err;
	int i;
	if (!ev_press) {
		if (filp->f_flags & O_NONBLOCK)
			return -EAGAIN;
		else 
			wait_event_interruptible(button_waitq, ev_press);
	}
	
	ev_press = 0;
	
	err = copy_to_user((void *)buff, (const void *)(&key_values),
				min(sizeof(key_values), count));

	unsigned int tmp;
	//gpio0-1 output mode
	tmp = readl(S3C64XX_GPMCON);
	tmp &= (~0xffff);
	tmp |= 0x1111;
	writel(tmp, S3C64XX_GPMCON); 

	//led
	for (i = 0; i < sizeof(button_irqs)/sizeof(button_irqs[1]); i++) {
		if (key_values[i])
			break;
	}
	iowrite32((1<<i), S3C64XX_GPMDAT);
	return 0;
}

int dev_close(struct inode *inode, struct file *filp)
{
	int i;
	for (i = 0; i< sizeof(button_irqs)/sizeof(button_irqs[1]); i++) {
		if (button_irqs[i].irq < 0)
			continue;
		free_irq(button_irqs[i].irq, (void *)&button_irqs[i])	;
	}
	return 0;

}

struct file_operations dev_fops = {
	.owner		= 	THIS_MODULE,
	.open		=	dev_open,
	.read		=	dev_read,	
	.release	=	dev_close,
};

struct miscdevice misc = {
	.minor = 0,
	.name = DEV_NAME,
	.fops = &dev_fops,
};

static int __init dev_init(void)
{
	int ret;

	ret = misc_register(&misc);

	return ret;
}

static void __exit dev_exit(void)
{
	misc_deregister(&misc);
}
module_init(dev_init);
module_exit(dev_exit);
MODULE_LICENSE("GPL");
