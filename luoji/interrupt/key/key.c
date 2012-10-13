#define GPMCON		(*((volatile unsigned long *)0x7f008820))
#define GPMDAT		(*((volatile unsigned long *)0x7f008824))
#define GPNCON		(*((volatile unsigned long *)0x7f008830))
#define GPNDAT		(*((volatile unsigned long *)0x7f008834))

void key(void)
{
	unsigned long key = 0x0;

	GPMCON &= ~(0xffff);
	GPMCON |= (0x1111);

	GPNCON &= ~(0xffffff);
	GPMDAT = key;

	while (1) {
		while (GPNDAT == 0x7f);
		while (GPNDAT != 0x7f);

		key = ~key;
		GPMDAT = key;
	}
}
