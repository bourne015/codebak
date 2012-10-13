#include<stdio.h>
void main()
{
	int i,j;
	int a[50],n = 0,sum = 0;
	for(i=2; i<1000; i++) {
		for(j=1; j<i; j++)
			if((i%j) == 0) {
				a[n] = j;
				sum += j;
				n++;
			}
		if(sum == i) {
			printf("%d = ",i);
			for(j=0; j<(n-1); j++)
				printf("%d+",a[j]);
				printf("%d",a[n-1]);
		printf("\n");
		}
	sum = 0;
	n = 0;
	}
}
