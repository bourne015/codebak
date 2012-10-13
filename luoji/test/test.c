#define	gpmcon  (*((volatile unsigned long *)0x7F008820))
#define	gpmdat  (*((volatile unsigned long *)0x7F008824))

void dl()
{
	volatile int i = 3000;
	volatile int j = 3000;
	
	for (i = 3000; i >= 0; i--)
		for (j = 3000; j >= 0; j--);
}

int test()
{
	unsigned long key = 0xc;

	gpmcon &= ~0xffff;
	gpmcon |= 0x1111;
//	while (1) {
//		key = key >> 1;
		gpmdat = key;
//		dl();
//	}
}

int test2()
{
	unsigned long key = 0x0;

	gpmcon &= ~0xffff;
	gpmcon |= 0x1111;
		gpmdat = key;
}
