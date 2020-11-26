#include <stdio.h>

int num_one(int *a, int len)
{
    int i, s;

    s = a[0];
    for (i = 1; i < len; i++)
        s ^= a[i];
    return s;
}

int main(void)
{
    int a[] = {1,1,2,2,3,4,4,4};

    printf("%d\n", num_one(a, sizeof(a)/sizeof(int)));
}


