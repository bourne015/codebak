#include<stdio.h>
#include<string.h>
void main(void)
{
	char p1[30] = "this is p1";
	char p2[] = "this is p2";
	char *p = p1;
	int i = 0, j = 0;
	//mystrcat(p1, p2);
	while (p1[i++] != '\0')
		;
	i--;
	printf("p :%s\n",p);
	while (p1[i++] = p2[j++])
		;
	printf("p :%s\n",p);
}
