#include <stdio.h>
//int a[][4] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
//int a[][5] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
int a[][2] = {1,2,3,4};
int t = 2;

void printmatrix(int a[][t], int start, int n, int totle)
{
    int i;

    for (i = 0; i < n; i++)
        printf("%d ", a[start][start+i]);

    for (i = 0+1; i < n; i++)
        printf("%d ", a[start+i][totle-start-1]);

    for (i = 0+1; i < n; i++)
        printf("%d ", a[totle-start-1][totle-start-1-i]);

    for (i = 0+1; i < n-1; i++)
        printf("%d ", a[totle-start-1-i][start]);
    printf("\n");
}

void circlematrix(int a[][t], int cols)
{
    int circle, start = 0;
    int n = cols;

    if (cols%2 == 0)
        circle = cols/2;
    else
        circle = cols/2 + 1;

    while (circle > 0) {
        printmatrix(a, start, n, cols);
        n -= 2;
        circle--;
        start++;
    }
}

void main(void)
{

    circlematrix(a, t);
}
