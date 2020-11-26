#include <stdio.h>

int find(int a[4][4], int row, int col, int num)
{
    int i, j;

    for (i = 0; i < row;i++) {
        for (j = col; j >= 0; j--) {
            if (a[i][j] == num) {
                printf("found: a[%d][%d]\n", i, j);
                return 1;
            } else if (a[i][j] > num) {
                col--;
            } else
                continue;
        }
    }
    return 0;
}

int main(void)
{
    int a[4][4] = {1,2,8,9,2,4,9,12,4,7,10,13,6,8,11,15};

    find(a, 4, 4, 15);
    return 0;
}
