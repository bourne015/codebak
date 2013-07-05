#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define solves	5
#define num	7

data[solves][num] /*5=solves, 0=id, 1-6=red, 7=blue*/

int main(void)
{
	int total;

	srand(time(NULL));

        printf("input the times to create:");
        scanf("%d", &total);

	for (; total >= 0; --total)
		create();	//create the data
	
}
