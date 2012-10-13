#include<stdio.h>
#define n 9
int a[n];
void main()
{
	int i,j;
	for(i=0; i<n; i++)
		scanf("%d",&a[i]);
	max();
	for(i=0; i<n; i++) {
	if(i%3==0&&i!=0) 
		printf("\n");	
		printf("%d\t",a[i]);
	}
	printf("\n");
}

int max()
{
	int i,j,t;
	for(j=0; j<n; j++)
	for(i=0; i<n-1; i++) {
		if(a[i]>a[i+1]) {
			a[i+1]=t;
			a[i+1]=a[i];
			a[i]=t;
		}
	}
	return a[n-1];
		
}

int min()
{
	int i,j,t;
	for(j=0; j<n; j++)
	for(i=0; i<n-1; i++) {
		if(a[i]>a[i+1]) {
			a[i+1]=t;
			a[i+1]=a[i];
			a[i]=t;
		}
	}
	return a[0];
}		
