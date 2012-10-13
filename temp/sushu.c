#include<stdio.h>

void main()
{
	int i,j;
	int flag;
	for(i=0;i<15;i++) {
	for(j=2;j<i;j++) 
	{
		if(i%j!=0)
			flag=1;
		else {
			flag=0;
			break;
		}
	}
	if(flag==1)
		printf("%d\n",i);
	}
}

