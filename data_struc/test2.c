#include <stdio.h>

int times = 0;

test(int i)
{
	if (i < 5) {
		i++;
		test(i);
		test(i+1);
		printf("times %d: i = %d\n", ++times, i);
	}
}

int main(void)
{
	test(0);
}
