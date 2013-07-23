#include <stdio.h>

#define NUM 5

void quick(int a[], int l, int r)
{
	int  i = l, j = r;
	int tmp;

	if (l < r) {
		tmp = a[i];
		while (i < j) {
			while (i < j && a[j] > tmp)
				j--;
			if (i < j)
				a[i++] = a[j];

			while (i < j && a[i] < tmp)
				i++;
			if (i < j) 
				a[j--] = a[i];		
		}
		a[i] = tmp;

		quick(a, l, i-1);
		quick(a, i+1, r);
	}
}

int main(void)
{
	int a[] = {5,4,3,2,1};
	int i = 0;
	
	quick(a, i, NUM-1);

	for (i =  0; i < NUM; i++)
		printf("%d ", a[i]);
	printf("\n");

	return 0;
}
