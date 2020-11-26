#include <stdio.h>

int jumpFloorII(int number)
{
    int i, fn1 = 1, fn2 = 1;

    if (number <= 0)
        return 0;
    for (i = 2; i <= number; i++) {
        fn2 = 2*fn1;
        fn1 = fn2;
    }
    return fn2;
}

int main(void)
{
    int n = 2, ret = 0;

    ret = jumpFloorII(n);
    printf("%d, %d\n", n, ret);
}
