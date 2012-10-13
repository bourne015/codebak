#include<stdio.h>
void main()
{
	int i,j=0;
	float sum=0,max=0,aver;
	scanf("%d",&i);
	while(i!=0) {
		if(i>max) 
			max=i;
		j++;
		sum+=i;
		scanf("%d",&i);
	}
	aver=sum/j;
	printf("max=%f,aver=%f\n",max,aver);
}
