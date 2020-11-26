#include <stdio.h>

int number_1(int n)
{
    unsigned int tmp = 1, cnt = 0;

    while (tmp) {
        if (n & tmp)
            cnt++;
        tmp = tmp << 1;
    }
    return cnt;
}

int main(void)
{
    int n = -2, ret = 0;

    ret = number_1(n);

    printf("%d: %d\n", n, ret);
}
