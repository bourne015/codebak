#define	gpmcon  (*((volatile unsigned long *)0x7F008820))
#define	gpmdat  (*((volatile unsigned long *)0x7F008824))

void dl()
{
	volatile int i = 3000;
	volatile int j = 3000;
	
	for (i = 300; i >= 0; i--)
		for (j = 3000; j >= 0; j--);
}

int led1(void)
{
	unsigned long key = 0xe;

	gpmcon &= ~0xffff;
	gpmcon |= 0x1111;
	gpmdat = key;

	return 1;
}

int led2(void)
{
	unsigned long key = 0xc;

	gpmcon &= ~0xffff;
	gpmcon |= 0x1111;
	gpmdat = key;
	dl();
	return 1;
}

int led_run(void)
{
	unsigned long key = 0xeeeeeeee;
	int i = 0;
	gpmcon &= ~0xffff;
	gpmcon |= 0x1111;
	
	while (i++ < 4) {
		key = key >> 1;
		gpmdat = key;
		dl();
	}
	gpmdat = 0x0;
	dl();
	return 1;
}

int led_off(void)
{
	unsigned long key = 0xf;

	gpmcon &= ~0xffff;
	gpmcon |= 0x1111;
	gpmdat = key;

	return 1;
}
