#include<stdio.h>
void main()
{
	int i,a[5];
	for(i=0; i<=1993; i++) 	{
		a[1]=i%10;
		a[2]=(i/10)%10;
		a[3]=(i/100)%10;
		a[4]=i/1000;
		if(a[1]==a[4]&&a[2]==a[3])
			printf("%d%d%d%d\n",a[1],a[2],a[3],a[4]);
	}
}
