#include <stdio.h>

void swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int mid3(int *a, int left, int right)
{
	int center = (left + right)/2;

	if (a[left] > a[right])
		swap(&a[left], &a[right]);
	if (a[left] > a[center])
		swap(&a[left], &a[center]);
	if (a[center] > a[right])
		swap(&a[center], &a[right]);

	swap(&a[center], &a[right]);

	return a[right];
}

void quick(int *a, int left, int right)
{
	int i = left, j = right-1;

	if (left < right) {
		int tmp = mid3(a, left, right);

		while (1) {
			while (a[i] < tmp) i++;
			while (a[j] > tmp) j--;

			if (i < j)
				swap(&a[i], &a[j]);
			else
				break;
		}
		swap(&a[i], &a[right]);
	
		quick(a, left, i);
		quick(a, i+1, right);
	}
}
