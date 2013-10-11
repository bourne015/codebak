#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/poll.h>
#include <linux/types.h>
#include <linux/irq.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>
#include <mach/hardware.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/miscdevice.h>
#include <linux/sched.h>

#include <mach/map.h>
//#include <mach/regs-clock.h>
#include <mach/regs-gpio.h>

//#include <plat/gpio-cfg.h>
#include <mach/gpio-bank-n.h>
#include <mach/gpio-bank-m.h>

#define DEVICE_NAME     "buttons"

int key_major = 251;
struct class *myclass;

struct button_irq_desc {
    int irq;
    int number;
    char *name; 
};

static struct button_irq_desc button_irqs [] = {
    {IRQ_EINT( 0), 0, "KEY0"},
    {IRQ_EINT( 1), 1, "KEY1"},
    {IRQ_EINT( 2), 2, "KEY2"},
    {IRQ_EINT( 3), 3, "KEY3"},
    {IRQ_EINT( 4), 4, "KEY4"},
    {IRQ_EINT( 5), 5, "KEY5"},
};

static volatile char key_values [] = {'0', '0', '0', '0', '0', '0', '0', '0'};

static DECLARE_WAIT_QUEUE_HEAD(button_waitq);

static volatile int ev_press = 0;

static irqreturn_t buttons_interrupt(int irq, void *dev_id)
{
	struct button_irq_desc *button_irqs = (struct button_irq_desc *)dev_id;
	int down;
 	int number;
	unsigned tmp;

	udelay(0);
	number = button_irqs->number;
	switch(number) {
		case 0: case 1: case 2: case 3: case 4: case 5:
		 	tmp = readl(S3C64XX_GPNDAT);
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

    	return IRQ_RETVAL(IRQ_HANDLED);
}


static int
s3c64xx_buttons_open(struct inode *inode, struct file *file)
{
	int i;
    	int err = 0;
    
    	for (i = 0; i < sizeof(button_irqs)/sizeof(button_irqs[0]); i++) {
		if (button_irqs[i].irq < 0) {
			continue;
    		}
     		err = request_irq(button_irqs[i].irq, buttons_interrupt,
				IRQ_TYPE_EDGE_BOTH, button_irqs[i].name,
				(void *)&button_irqs[i]);
        	if (err)
        		break;
    	}

	if (err) {
    		i--;
        	for (; i >= 0; i--) {
			if (button_irqs[i].irq < 0) {
				continue;
     			}
     			disable_irq(button_irqs[i].irq);
     	        	free_irq(button_irqs[i].irq, (void *)&button_irqs[i]);
		}
        	return -EBUSY;
    	}
    	ev_press = 1;
    	return 0;
}

static int
s3c64xx_buttons_close(struct inode *inode, struct file *file)
{
	int i;
    
    	for (i = 0; i < sizeof(button_irqs)/sizeof(button_irqs[0]); i++) {
 		if (button_irqs[i].irq < 0) {
     			continue;
		}
		free_irq(button_irqs[i].irq, (void *)&button_irqs[i]);
	}

    	return 0;
}

static int
s3c64xx_buttons_read(struct file *filp, char __user *buff,
				size_t count, loff_t *offp)
{
	unsigned long err;

	if (!ev_press) {
		if (filp->f_flags & O_NONBLOCK)
			return -EAGAIN;
		 else
		 	wait_event_interruptible(button_waitq, ev_press);
    	}
    
    	ev_press = 0;

	err = copy_to_user((void *)buff, (const void *)(&key_values),
			min(sizeof(key_values), count));

//add from here	with all led on or off
	unsigned tmp;
        //gpm0-3 output mode
        tmp =readl(S3C64XX_GPMCON);
        tmp &= (~0xFFFF);
        tmp |= 0x1111;
        writel(tmp,S3C64XX_GPMCON);

        //gpm0-3 output 0
        tmp =readl(S3C64XX_GPMDAT);
        iowrite32((~tmp), S3C64XX_GPMDAT);

//till here
    	return err ? -EFAULT : min(sizeof(key_values), count);
}
/*
static unsigned int s3c64xx_buttons_poll( struct file *file,
					struct poll_table_struct *wait)
{
    	unsigned int mask = 0;
    	poll_wait(file, &button_waitq, wait);
    	if (ev_press)
    		mask |= POLLIN | POLLRDNORM;
    	return mask;
}
*/
static struct file_operations key_fops = {
    	.owner   =   THIS_MODULE,
    	.open    =   s3c64xx_buttons_open,
    	.release =   s3c64xx_buttons_close, 
    	.read    =   s3c64xx_buttons_read,
//    	.poll    =   s3c64xx_buttons_poll,
};

static int __init dev_init(void)
{
	key_major = register_chrdev(0, "key", &key_fops);

        myclass = class_create(THIS_MODULE, "dev_key");
        device_create(myclass, NULL, MKDEV(key_major, 0), NULL, "key");
 
	printk (DEVICE_NAME "\tinitialized\n");

	return 0;
}

static void __exit dev_exit(void)
{
	unregister_chrdev(key_major, "key");

	device_destroy(myclass, MKDEV(key_major, 0));
        class_destroy(myclass);
}

module_init(dev_init);
module_exit(dev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("fantao");
