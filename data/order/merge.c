#include <stdio.h>
#include <stdlib.h>

void
merge(int *a, int *array, int left, int right, int rightend)
{
        int i, leftend, tmp;
        int numele = rightend - left + 1;
        tmp = left;
        leftend = right -1;

        while (left <= leftend && right <= rightend)
                if (a[left] <= a[right])
                        array[tmp++] = a[left++];
                else
                        array[tmp++] = a[right++];

        while (left <= leftend)
                array[tmp++] = a[left++];
        while (right <= rightend)
                array[tmp++] = a[right++];

        for (i = 0; i < numele; i++, rightend--)
                a[rightend] = array[rightend];
}

void sort(int *a, int *tmp, int left, int right)
{
        int mid;
        if (left < right) {
                mid = (left+right)/2;
                sort(a, tmp, left, mid);
                sort(a, tmp, mid+1, right);
                merge(a, tmp, left, mid+1, right);
        }
}

int msort(int *a, int left, int right)
{
	int *tmp;

	tmp = malloc((right + 1) * sizeof (int));
	if (tmp == NULL) {
		printf("failed to malloc tmo\n");	
		return -1;
	}
	
	sort(a, tmp, left, right);
	
	return 0;
}
