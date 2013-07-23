#include <stdio.h>
#include <stdlib.h>

#define N 8

void
merge(int array[], int left, int right, int rightend);
void
msort(int array[], int left, int right);

int a[N] = {3,1,4,1,5,9,2,6};

int main(void)
{
	int i;
	int *array;
	array = malloc(N*sizeof(int));
	msort(array, 0, N-1);
        for (i = 0; i < N; i++)
               printf("%d  ", a[i]);
	printf("\n");
}

void
merge(int array[], int left, int right, int rightend)
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

void
msort(int array[], int left, int right)
{
        int mid;
        if (left < right) {
                mid = (left+right)/2;
                msort(array, left, mid);
                msort(array, mid+1, right);
                merge(array, left, mid+1, right);
        }
}

