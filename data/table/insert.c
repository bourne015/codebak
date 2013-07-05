#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX	9	
int a[] = {9,8,7,6,5,4,3,2,1};

void insert(void)
{
	int i, j, tmp;
	int inc;

	for (inc = 2; inc > 0; inc /= 2) 
	for (i = inc; i < MAX; i++) {
		tmp = a[i];
		for (j = i; j >= inc; j -= inc)
			if (tmp < a[j-inc])
				a[j] = a[j-inc];
			else 
				break;
		a[j] = tmp;
	}

	for (i = 0; i < MAX; i++)
		printf("%d ", a[i]);
	printf("\n");

}

int main(void)
{
	insert();
}
