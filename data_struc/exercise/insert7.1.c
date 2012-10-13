#include <stdio.h>

int main(void)
{
	int a[] = {1,1,1,1,1,1,1,1,1};
	int i, j, tmp;

	for (i = 0; i < 9; i++)
		printf("%d ", a[i]);
	printf("\n");

	for (i = 0; i < 9; i++) {

		tmp = a[i];
		for (j = i; j > 0; j--)
			if (a[j-1] > tmp) {
				a[j] = a[j-1];
			} else
				break;
		a[j] = tmp;
	}

	for (i = 0; i < 9; i++)
		printf("%d ", a[i]);
	printf("\n");
	
}
