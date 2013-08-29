#define GPMCON		(*((volatile unsigned long *)0x7f008820))
#define GPMDAT		(*((volatile unsigned long *)0x7f008824))
#define GPNCON		(*((volatile unsigned long *)0x7f008830))
#define GPNDAT		(*((volatile unsigned long *)0x7f008834))

#define EINT0CON0	(*((volatile unsigned long *)0x7f008900))
#define EINT0MASK	(*((volatile unsigned long *)0x7f008920))
#define EINT0PEND	(*((volatile unsigned long *)0x7f008924))
#define VIC0INTENABLE	(*((volatile unsigned long *)0x71200010))
#define VIC0ADDRESS	(*((volatile unsigned long *)0x71200f00))
#define VIC0IRQSTATUS	(*((volatile unsigned long *)0x71200000))
#define VIC0VECTADDR0      (*((volatile unsigned long *)0x71200100))
#define VIC0VECTADDR1      (*((volatile unsigned long *)0x71200104))

#define VIC1IRQSTATUS	(*((volatile unsigned long *)0x71300000))
#define VIC1INTENABLE	(*((volatile unsigned long *)0x71300010))
#define VIC1ADDRESS	(*((volatile unsigned long *)0x71300f00))
#define VIC1VECTADDR5	(*((volatile unsigned long *)0x71300114))

void key0_4_irq(void)
{
	int i;
	GPMCON &= ~(0xffff);
	GPMCON |= 0x1111;

	for (i = 0; i < 6; i++) {
		if (EINT0PEND & (1 << i)) {
			if (GPNDAT & (1 << i))
				GPMDAT &= ~(1 << i);
			else 
				GPMDAT |= (1 << i);
		}
	}
}

void key5_6_irq(void)
{
	int i = 0;

	GPMCON &= ~(0xffff);
	GPMCON |= 0x1111;

	for (i = 4; i < 6; i ++) {
		if (EINT0PEND & (1<<i)) {
			if (GPNDAT & (1<<i))
				GPMDAT = 0xf;
			else
				GPMDAT = 0x0;
		}
	}
}

void key_irq_init()
{
	/*set GPIO to interrupt mode*/
	GPNCON &= ~(0xfff);
	GPNCON |= (0xaaa);

	/*set signal method,both edge*/
	EINT0CON0 &= ~(0xfff);
	EINT0CON0 |= 0x777;

	/*enable*/
	EINT0MASK &= ~(0x3f);

	/*enable VIC0(eint0-5)*/
	VIC0INTENABLE |= 0x3;

	VIC0VECTADDR0 = key0_4_irq;
	VIC0VECTADDR1 = key5_6_irq;
}

void uart_irq(void)
{
	do_uart_irq();
	VIC1ADDRESS = 0;
}

void uart_irq_init()
{
	//uart0 == int37
	VIC1INTENABLE |= (1 << 5);
	VIC1VECTADDR5 = uart_irq;
}

void irq_init(void)
{
	key_irq_init();
	uart_irq_init();
}


void do_irq()
{
	int i = 0;
	void (*irq_isr)(void);

	if (VIC0IRQSTATUS) {
		irq_isr = VIC0ADDRESS;
		irq_isr();

		//clear the interrupt
        	EINT0PEND = 0x3f;
        	VIC0ADDRESS = 0;
		//VIC0INTENCLEAR |= (0x3);
	} else if (VIC1IRQSTATUS) {
		irq_isr = VIC1ADDRESS;
		irq_isr();
	}
}
