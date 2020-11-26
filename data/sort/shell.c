#include "order.h"

void shell_sort(int *b)
{
    int i, j, step, tmp;

    for (step = MAX/2; step > 0; step /= 2) {
        for (i = step; i < MAX; i++) {
            tmp = b[i];
            for (j = i; j >= step && b[j-step] > tmp; j -= step)
                b[j] = b[j-step];
            b[j] = tmp;
        }
    }
}

