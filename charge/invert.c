#include <stdio.h>

int invert(unsigned int x, int p, int n)
{
	unsigned int t;
	unsigned int bit;
	bit = ((~0x0 << p+1) | ~(~0x0 << p-n+1)); //set the bits to 0
	t = x & bit; //clear the bits
	printf("%u\n", t);

	x = t | (~x & ~bit);
	printf("%u\n", x);
}

int main()
{
	unsigned int x = 32;
	int p = 6;
	int n = 2;
	invert(x, p, n);
}
