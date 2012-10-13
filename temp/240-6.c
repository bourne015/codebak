#include<stdio.h>
#define n 20

int cut(char *p1, char *p2, int p, int m)
{	
	int i;
	//p1 = p;
	for(i=0; i<m; i++)
		*(p2+i)=*(p1+p+i);
	return p2;	
}

void main()
{
	char s1[n]="hello,world";
	char s2[n];
	char *p;
	int i;
	p = cut(&s1[0], &s2[0], 3, 8);
	for(i=0; i<8; i++)
		printf("%c",s2[i]);
	printf("\n");
}
