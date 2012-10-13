#define	gpmcon  (*((volatile unsigned long *)0x7F008820))
#define	gpmdat  (*((volatile unsigned long *)0x7F008824))

volatile int j = 0x12345678;
volatile int k = 0;
volatile int g;

void delay()
{
	volatile int i = 30000;
	while (i--);
}

int main()
{
	unsigned long key = 0xeeeeeeee;

	gpmcon &= ~0xffff;
	gpmcon |= 0x1111;
	while (1) {
		key = key >> 1;
		gpmdat = key;
		delay();
	}
}

