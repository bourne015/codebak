#define	gpmcon  (*((volatile unsigned long *)0x7F008820))
#define	gpmdat  (*((volatile unsigned long *)0x7F008824))

void delay2()
{
	volatile int i = 30000;
	while (i--);
}

int main2()
{
	int i = 16;
	unsigned long key = 0xb;

	gpmcon &= ~0xffff;
	gpmcon |= 0x1111;
//	while (i--) {
//		key = key >> 1;
		gpmdat = key;
//		delay();
//	}
}

