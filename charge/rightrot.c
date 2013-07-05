#include <stdio.h>

unsigned int
rightrot(unsigned int x, int n)
{
	unsigned int stack;

	stack = x << (8*sizeof(unsigned int) - n);
	x = x >> n | stack;
	printf("%u\n", x);
	return x;
}

void to_sixty(unsigned int x)
{
	int a[32], i = 0;
	while (x) {
		a[i] = x%16;
		x /= 16;
		i++;
	}
	i--;
printf("0x");
        while (i >= 0) {
		if ((i+1)%4 == 0)
                        printf(" ");
                if (a[i] > 9) {
                        a[i] = (char)(a[i] + 55);
                        printf("%c", a[i--]);
                }
                else
                        printf("%d", a[i--]);
        }
	
	printf("\n");
}

int main()
{
	unsigned x = 0xf;
	int n =2;
	//right cycle shift
	x = rightrot(x, n);

	to_sixty(x);
}
