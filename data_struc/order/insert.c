#include "order.h"

void insert_order(void)
{
        int i, j;
        int tmp;

        for (i = 1; i < MAX; i++ ) {
                tmp = b[i];
                for (j = i; j > 0 && (b[j -1] > tmp); j--)
                        b[j] = b[j-1];
                b[j] = tmp;
        }
        return;

//real  0m0.319s
//user  0m0.120s
//sys   0m0.012s
}

