#include <stdio.h>

#define CNT 5

void myprint(int a[CNT][CNT], int start, int end)
{
    int i;

    //up
    for (i = start; i <= end; i++)
        printf("%d\n", a[start][i]);
    //right
    for (i = start+1; i <= end; i++)
        printf("%d\n", a[i][end]);
    //down
    for (i = end-1; i >= start; i--)
        printf("%d\n", a[end][i]);
    //left
    for (i = end-1; i > start; i--)
        printf("%d\n", a[i][start]);
}

void printmatrix(int a[CNT][CNT], int row, int col)
{
    int i, cir;

    if (row <= 0 || col <= 0)
        return;
    if (row%2 == 0)
        cir = row/2;
    else
        cir = row/2 + 1;

    for (i = 0; i < cir; i++)
        myprint(a, i, row-1-i);
}

int main(void)
{
    int row = CNT, col = CNT;
    //int a[CNT][CNT] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    int a[CNT][CNT] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
    //int a[CNT][CNT] = {7,6,4,5};

    printmatrix(a, row, col);
}
