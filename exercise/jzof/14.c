#include <stdio.h>

int main(void)
{
    int a[]= {1,2,3,4,5,6,7,8,9, 10};
    int i, j, t;

    for (i = 0; i < 10; i++) {
        for (j = i; j < 9; j++) {
            if (a[j]%2 == 0 && a[j+1]%2 == 1) {
                t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
            }
        }
    }
    for (i = 0; i < 10; i++)
        printf("%d\n", a[i]);
}
