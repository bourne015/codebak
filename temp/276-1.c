#include<stdio.h>
#define s 3
#define man 3
struct student {
		int num;
		char name[10];
		float score[s]
	}stu[man];

float aver(float *p,int n)
{
	int i;
	float sum=0;
	for(i=0; i<n; i++) {
		sum+=*(p+i);
	}
	return (float)(sum/n);
}

void main()
{		
	int i,j;
	float a;
	printf("input num,name,score:");
	for(j=0; j<man; j++) {
		scanf("%d %s",&(stu[j].num),stu[j].name);
		for(i=0; i<s; i++)
			scanf("%f",&stu[j].score[i]);
	}
	for(j=0; j<man; j++) {
//		puts(stu[j].name);
		a = aver(&stu[j].score,s);
		printf("%s:%.2f\n",stu[j].name,a);
	}
}

