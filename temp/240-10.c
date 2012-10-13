#include<stdio.h>
#include<stdlib.h>
//#define m 2
#define n 3

int sum(int *p, int l)
{
	int i,j,s=0;	
	for(i=0; i<l*n; i++) {
		s+=*(p+i);
	}
	return s;
}

void main()
{
	int (*p)[n],(*p1)();
	int i,j,m,s;
	printf("intput the rank:");
	scanf("%d",&m);
	p=(int (*)[n])malloc(3*m*sizeof(int));
	if(!p) {
		printf("malloc error!\n");
	}
	for(i=0; i<m; i++)
	for(j=0; j<n; j++) 
		p[i][j] = i+j;
	for(i=0; i<m; i++) {
	for(j=0; j<n; j++) {
		printf("%d\t",p[i][j]);
	}
		printf("\n");
	}	
//	p1 = sum;
	s = sum(&p[0][0],m);	
	printf("sum=%d\n",s);
	free(p);
}
