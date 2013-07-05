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

#include <asm/gpio.h>
#include <asm/io.h>
#include <mach/regs-gpio.h>
#include <mach/map.h>
#include <mach/gpio-bank-n.h>
#include <mach/gpio-bank-m.h>

struct pin_desc{
	int irq;
	char *name;
	unsigned int pin;
	unsigned int key_val;
};

struct pin_desc pins_desc[4] = {
	{IRQ_EINT(0), "K1",  S3C64XX_GPN(0), KEY_L},
	{IRQ_EINT(1), "K2",  S3C64XX_GPN(1), KEY_S},
	{IRQ_EINT(2), "K3",  S3C64XX_GPN(2), KEY_ENTER},
	{IRQ_EINT(4), "K4",  S3C64XX_GPN(3), KEY_LEFTSHIFT},
};

static struct input_dev *keys_dev;
static struct pin_desc *irq_pd;
static struct timer_list keys_timer;

static irqreturn_t keys_irq(int irq, void *dev_id)
{
	irq_pd = (struct pin_desc *)dev_id;
	mod_timer(&keys_timer, jiffies + HZ/100);
	
	return IRQ_RETVAL(IRQ_HANDLED);
}

static void keys_timer_function(unsigned long data)
{
	struct pin_desc * pindesc = irq_pd;
	unsigned int pinval;

	if (!pindesc)
		return;

	//pinval = s3c_gpio_getcfg(pindesc->pin);
	pinval = (gpio_get_value(pindesc->pin) ? 1 : 0);

	if (pinval) {
		input_event(keys_dev, EV_KEY, pindesc->key_val, 0);
		input_sync(keys_dev);
	}
	else {

		input_event(keys_dev, EV_KEY, pindesc->key_val, 1);
		input_sync(keys_dev);
	}
}

static __init int keys_init(void)
{
	int i;
	
	keys_dev = input_allocate_device();

	set_bit(EV_KEY, keys_dev->evbit);
	set_bit(EV_REP, keys_dev->evbit);

	set_bit(KEY_L, keys_dev->evbit);
	set_bit(KEY_S, keys_dev->evbit);
	set_bit(KEY_ENTER, keys_dev->evbit);
	set_bit(KEY_LEFTSHIFT, keys_dev->evbit);
	
	input_register_device(keys_dev);
	
	init_timer(&keys_timer);
	keys_timer.function = keys_timer_function;
	add_timer(&keys_timer);

	for (i = 0; i < 4; i++) {
		request_irq(pins_desc[i].irq, keys_irq, IRQ_TYPE_EDGE_BOTH,
				 pins_desc[i].name, &pins_desc[i]);
	}

	return 0;
}

static __exit void keys_exit(void)
{
	int i;

	for (i = 0; i < 4; i++) {
		free_irq(pins_desc[i].irq, &pins_desc[i]);
	}

	del_timer(&keys_timer);
	input_unregister_device(keys_dev);
	input_free_device(keys_dev);
}

module_init(keys_init);
module_exit(keys_exit);
MODULE_LICENSE("GPL");
