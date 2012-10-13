#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void main()
{
	char a[20],b[20];
	gets(a);
	while((gets(a))!={"stop"}) {
		printf("%d\n",strlen(gets(a)));
	}
}
