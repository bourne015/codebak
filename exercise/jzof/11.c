#include <stdio.h>

double mypow(double base, int exp)
{
    int i, flag = 0;
    double ret = 1;

    if (exp == 0)
        return 1;
    if (exp == 1)
        return base;
    if (exp < 0) {
        exp = -1*exp;
        flag = 1;
    }
    for (i = 1; i <= exp; i++)
        ret *= base;

    if (flag)
        return (1/ret);
    else
        return ret;
}

int main(void)
{
    double base = 4, ret = 0;
    int exp = -2;

    ret = mypow(base, exp);
    printf("%f exp %d = %f\n", base, exp, ret);
}
