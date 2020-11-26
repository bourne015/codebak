#include <stdio.h>
#include "../create.h"

int max_array(int *a, int len)
{
    int i, fn1, fn2, max;

    fn2 = a[0];
    max = a[0];
    for (i = 1; i < len; i++) {
        if (fn2 > 0)
            fn1 = fn2 + a[i];
        else
            fn1 = a[i];
        fn2 = fn1;
        if (fn1 > max)
            max = fn1;
    }
    return max;
}

int main(void)
{
    int a[] = {-1,-2,-3};
    int ret = 0;

    ret = max_array(a, sizeof(a)/sizeof(int));
    print_array(a, sizeof(a)/sizeof(int));
    printf("sum: %d\n", ret);
}
