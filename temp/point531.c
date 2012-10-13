#include<stdio.h>
#define n 9
int a[n];

int max()
{
	int i,t1=0;
	for(i=0; i<n-1; i++) {
		if(a[i]>a[i+1]&&a[i]>=a[t1])
			t1=i;
		else if(a[i+1]>a[i]&&a[i+1]>=a[t1])
			t1=i+1;
	}
	printf("max=%d\n",a[t1]);
	return t1;
}

int min()
{
	int i,t2=0;
	for(i=0; i<n-1; i++) {
		if(a[i]<a[i+1]&&a[i]<=a[t2])
			t2=i;
		else if(a[i+1]<a[i]&&a[i+1]<=a[t2])
			t2=i+1;
	}
	printf("min=%d\n",a[t2]);
	return t2;
}

void swap1(int *p1,int *p2)
{
	int t;
	t=*p1;
	*p1=*p2;
	*p2=t;
}

void swap2(int *p1,int *p2)
{
	int t;
	t=*p1;
	*p1=*p2;
	*p2=t;
}

void main()
{
	int i,x,m,(*p1)(),(*p2)();
	for(i=0; i<n; i++)
		scanf("%d",&a[i]);
	x=max();
	p1=swap1;
	(*p1)(&a[x],&a[2]);
	m=min();
	p2=swap2;
	(*p2)(&a[m],&a[6]);
	for(i=0; i<n; i++) {
		if(i%3==0&&i!=0)
			printf("\n");
		printf("%d\t",a[i]);
	}
	printf("\n");
}
