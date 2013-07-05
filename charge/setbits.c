#include <stdio.h>

void
setbits(unsigned int x, int p, int n, unsigned y)
{
	unsigned int bits;
	//bits = (~0x0 << p+1) | ~(~0x0 << p-n+1); //set the bit to 0
	
	x |= ((y & ~(~0x0 << n)) << p-n+1);
	
	printf("y %u\n", ((y & ~(~0x0 << n)) << p-n+1));
	printf("x %u\n", x);
}

int main()
{
	unsigned x = 0xe, y = 0x1;
	int n = 2, p = 1;
	setbits(x, p, n, y);
}
