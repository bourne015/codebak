#include "order.h"

void insert(int *dat)
{
    int i, j, tmp;

    for (i = 1; i < MAX; i++ ) {
        tmp = dat[i];
        for (j = i; j > 0 && (dat[j-1] > tmp); j--)
            dat[j] = dat[j-1];
        dat[j] = tmp;
    }
}

