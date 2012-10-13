#include <stdio.h>

int main(void)
{
	int a[] = {9,8,7,6,5,4,3,2,1};
	int inc, i, j, tmp;

	for (i = 0; i < 9; i++)
		printf("%d ", a[i]);
	printf("\n");

	for (inc = 5; inc > 0; inc /= 2)
	for (i = inc; i < 9; i++) {
		tmp = a[i];
		for (j = i; j >= inc; j -= inc) {
			if (tmp < a[j-inc])
				a[j] = a[j-inc];
			else
				break;
		}
		a[j] = tmp;
	}

	for (i = 0; i < 9; i++)
		printf("%d ", a[i]);
	printf("\n");
}
