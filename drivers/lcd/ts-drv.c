#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/clk.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>

#include <asm/irq.h>
#include <asm/io.h>
#include <plat/regs-adc.h>

#include <mach/hardware.h>
#include <mach/ts.h>
#include <mach/irqs.h>

#define S3C_TS_BASE 0x7e00b000

typedef struct s3c_ts_regs {
	volatile unsigned long adccon;
	volatile unsigned long adctsc;         
	volatile unsigned long adcdly;          
	volatile unsigned long adcdat0;        
	volatile unsigned long adcdat1;         
	volatile unsigned long adcupdn;         
	volatile unsigned long adcclrint;
	volatile unsigned long reserved; 
	volatile unsigned long adcclrintpndnup;
} s3c_ts_regs;

//static void __iomem	*ts_base;
s3c_ts_regs *ts_base;

static void detect_stylus_up(void)
{
	ts_base->adctsc = 0x1d3;
}

static void detect_stylus_down(void)
{
	ts_base->adctsc = 0xd3;
}

static void set_measure_mode(void)
{
	//auto x/y conversion mode
	ts_base->adctsc = (1<<3) | (1<<2);
}

static irqreturn_t stylus_up_down(int irqno, void *param)
{
	if (ts_base->adcdat0 & (1<<15)) {
		//stylus up
		printk(KERN_ALERT "adc up\n");
		detect_stylus_down();
	} else {
		//stylus down
		printk(KERN_ALERT "adc down\n");
		
		set_measure_mode();
		//star adc convert
		ts_base->adccon |= 0x01;
	}
	//clear stylus irq_up_down
	ts_base->adcclrintpndnup = 0;

	return IRQ_HANDLED;
}

static irqreturn_t irq_adc(int irqno, void *param)
{
	unsigned long x, y;

	x = ts_base->adcdat0 & 0x3ff;
	y = ts_base->adcdat0 & 0x3ff;
	printk(KERN_ALERT "x = %lu, y = %lu\n", x, y);

	//clear adc interrupt
	detect_stylus_up();
	ts_base->adcclrint = 0;

	return IRQ_HANDLED;
}

struct resource *res_irq, *res_adc;
static int __init s3c_ts_probe(struct platform_device *pdev)
{
	struct clk *ts_clk;

	ts_base = ioremap(S3C_TS_BASE, sizeof(struct s3c_ts_regs));
	ts_base->adccon = (1<<16) | (1<<14) | (14<<6);
	ts_base->adcdly = 10000 & 0xffff;

	ts_clk = clk_get(NULL, "adc");
	if (IS_ERR(ts_clk)) {
		printk(KERN_ALERT "failed to get adc clk\n");
		return -1;
	}
	clk_enable(ts_clk);

	res_irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	request_irq(res_irq->start, stylus_up_down, IRQF_SAMPLE_RANDOM,
			"ts-irq", NULL);	
	printk(KERN_ALERT "res_irq = %d\n", res_irq->start);

	res_adc = platform_get_resource(pdev, IORESOURCE_IRQ, 1);
	request_irq(res_adc->start, irq_adc, IRQF_SAMPLE_RANDOM,
			"ts-adc", NULL);	
	printk(KERN_ALERT "res_adc = %d\n", res_adc->start);
	detect_stylus_down();

	return 0;
}

static int s3c_ts_remove(struct platform_device *pdev)
{
	free_irq(res_adc->start, NULL);
	free_irq(res_irq->start, NULL);
	iounmap(ts_base);

	return 0;
}

static struct platform_driver s3c_drv = {
	.probe = s3c_ts_probe,
	.remove = s3c_ts_remove,
	.driver = {
		.name = "ok6410-ts",
		.owner = THIS_MODULE,
		
	},
};

static int __init s3c_ts_init(void)
{	
	return platform_driver_register(&s3c_drv);
}

static void __exit s3c_ts_exit(void)
{
	platform_driver_unregister(&s3c_drv);
}

module_init(s3c_ts_init);
module_exit(s3c_ts_exit);
MODULE_LICENSE("GPL");
