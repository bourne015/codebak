#define GPMCON		(*((volatile unsigned long *)0x7f008820))
#define GPMDAT		(*((volatile unsigned long *)0x7f008824))
#define GPNCON		(*((volatile unsigned long *)0x7f008830))
#define GPNDAT		(*((volatile unsigned long *)0x7f008834))

#define EINT0CON0	(*((volatile unsigned long *)0x7f008900))
#define EINT0MASK	(*((volatile unsigned long *)0x7f008920))
#define EINT0PEND	(*((volatile unsigned long *)0x7f008924))
#define VIC0INTENABLE	(*((volatile unsigned long *)0x71200010))
#define VIC0ADDRESS	(*((volatile unsigned long *)0x71200f00))

int i = 0;
int j;

void irq_init()
{
	GPMCON = 0x1111;
	GPMDAT = 0x6;
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

}

void do_irq()
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

	//clear the interrupt
	EINT0PEND = 0x3f;
	VIC0ADDRESS = 0;

}

