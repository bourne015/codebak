#include <stdio.h>

int main(void)
{
	int count = 0;
	int num = 6;

	do {
		count += num & 0x1;
	} while (num = num >> 1);

	printf("count:%d\n", count);
}
