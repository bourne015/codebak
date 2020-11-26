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
	int i = left, j = right;

	if (left < right) {
		//int tmp = mid3(a, left, right);
		int tmp = a[left];

		while (i < j) {
			while (i < j && a[j] >= tmp) j--;
			while (i < j && a[i] <= tmp) i++;

			if (i < j)
				swap(&a[i], &a[j]);
		}
		swap(&a[i], &a[left]);
	
		quick(a, left, i-1);
		quick(a, i+1, right);
	}
}
