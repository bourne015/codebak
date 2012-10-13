#include<stdio.h>
#define n 7
void main()
{
	int a[n]={1,2,3,4,6,7};
	int input,t,m;
	int i,j,k;
	scanf("%d",&input);
	for(i=0; i<n; i++) {
		if(input<a[i]) {
			k=i;
			for(j=n-1; j>i; j--)
				a[j]=a[j-1];
		break;
		}
	}
	printf("%d\n",input);
	a[k]=input;
	for(i=0; i<n; i++) {
		printf("%d  ",a[i]);
	}
}
