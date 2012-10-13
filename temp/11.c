#include<stdio.h>
void main()
{
	int k=1234;
	scanf("%d",&k);
	sort(k);
}
void  sort(int k)
{	
	int a[4],i,j,t;
	printf("here\n");
	a[0]=k%10;
	a[1]=(k/10)%10;
	a[2]=(k/100)%10;
	a[3]=k/1000;
	for(j=0; j<4; j++)
		for(i=0; i<3; i++) {
			if(a[i]<a[i+1]) {
				t=a[i+1];
				a[i+1]=a[i];
				a[i]=t;
			}
		}
//	sum=1000*a[3]+100*a[2]+10*a[1]+a[0];
//	return a[];
	for(i=0; i<4; i++)
	printf("%d",a[i]);
	printf("\n");
}
