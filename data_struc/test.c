#include <stdio.h>

int i = 0, j = 0;
msort(int l, int r)
{
	int c;

	if (l < r) {
		c = (l + r)/2;
		msort(l, c);
		printf("first %d:l = %d, r = %d, c = %d\n", ++i, l, r, c);
		msort(c+1, r);
		printf("secend %d:l = %d, c+1 = %d, r = %d\n", ++j, l, c+1, r);
	}
}

int main(void)
{
	msort(0, 4);	
}
