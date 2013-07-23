#include "order.h"

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
                b[i] = array[rightend];
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

