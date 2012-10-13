#define GPMCON	(*(volatile unsigned long *)0x7f008820)
#define GPMDAT	(*(volatile unsigned long *)0x7f008824)
#define GPMPUD	(*(volatile unsigned long *)0x7f008828)
#define GPNCON	(*(volatile unsigned long *)0x7f008830)
#define GPNDAT	(*(volatile unsigned long *)0x7f008834)
#define GPNPUD	(*(volatile unsigned long *)0x7f008838)

int main(void)
{
	int i;
	unsigned long key;

	GPMCON = 0x11111;
	GPMPUD = 0x00;
	GPNCON = 0xfffff000;

	key = 0xeeeeeeee;
	GPMDAT = 0xfa;

	while (1) {

		while (GPNDAT == 0x7f);
		while (GPNDAT != 0x7f);
		
		key = key >> 1;
		GPMDAT = key;
	}

	return 0;
}
