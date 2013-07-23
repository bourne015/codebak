#include "order.h"

void shell_data(void)
{
        int i, j, in;
        int tmp;

        for (in = MAX/2; in > 0; in /= 2)
        for ( i = in; i < MAX; i++) {
                tmp = b[i];

                for (j = i; j >= in; j -= in)
                        if (tmp < b[j-in])
                                b[j] = b[j-in];
                        else
                                break;
                b[j] = tmp;
        }

//real  0m0.302s
//user  0m0.012s
//sys   0m0.000s
}

