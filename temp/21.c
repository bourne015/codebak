#include<stdlib.h>
#include<stdio.h>
#define n 10
int a[n];
void main()
{	
	int i,k;
	srand((int)time(NULL));
	for(i=0; i<n; i++) {
		a[i]=rand()%(210-45)+45;
	}
	sort();
	k=aver();
	counter(k);
}
sort()
{
	int i,j,t;
	for(j=0; j<n; j++)
		for(i=0; i<n-1; i++) {
			if(a[i]<a[i+1]) {
				t=a[i+1];
				a[i+1]=a[i];
				a[i]=t;
			}
		}

	for(i=0; i<n; i++)	
		printf("%d\n",a[i]);
}

int aver()
{
	int sum=0,i,aver;	
	for(i=0; i<n; i++) {	
		sum+=a[i];
	}
	aver=sum/n;
	printf("aver=%d\n",aver);
	return aver;
}

void counter(int cmpa)
{
	int count=0,i;
	for(i=0; i<n; i++) {
		if(a[i] < cmpa) {
			count++;
		}
	}
	printf("counter:%d\n",count);
}
