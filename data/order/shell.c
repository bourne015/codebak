#include "order.h"

void shell(int *b)
{
        int i, j, in;
        int tmp;

        for (in = MAX/2; in > 0; in /= 2) {
        	for ( i = in; i < MAX; i++) {
                	tmp = b[i];

                	for (j = i; j >= in; j -= in) {
                	        if (tmp < b[j-in])
                	                b[j] = b[j-in];
                	        else
                	                break;
			}
                	b[j] = tmp;
        	}
	}
}

