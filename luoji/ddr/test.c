#define	gpmcon  (*((volatile unsigned long *)0x7F008820))
#define	gpmdat  (*((volatile unsigned long *)0x7F008824))

void dl()
{
	volatile int i = 3000;
	volatile int j = 3000;
	
	for (i = 3000; i >= 0; i--)
		for (j = 3000; j >= 0; j--);
}

int test1(void)
{
	unsigned long key = 0x1;

	gpmcon &= ~0xffff;
	gpmcon |= 0x1111;
	gpmdat = key;

	return 1;
}

int test2(void)
{
	unsigned long key = 0x3;

	gpmcon &= ~0xffff;
	gpmcon |= 0x1111;
	gpmdat = key;
	test1();
	return 1;
}
