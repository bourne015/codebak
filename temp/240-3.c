#include<stdio.h>
#define m 5
void  sort(int *x, int n)
{
	int i,j,t;
	for(j=0; j<n-1; j++)
	for(i=0; i<(n-1); i++) {
		if(*(x+i+1) > *(x+i)) {
			t = *(x+i+1);
			*(x+i+1) = *(x+i);
			*(x+i) = t;
		}
	}	
}

void main()
{
	int i,a[m],(*p)();
	for(i=0; i<m; i++)
		scanf("%d",&a[i]);
	p = sort;
	(*p)(&a[0], m);
	for(i=0; i<m; i++)
		printf("%d\t",a[i]);
	printf("\n");
}	
