#include<stdlib.h>
#include<string.h>
#include<stdio.h>
void main()
{
	char a[20],b[20],c[20];
	scanf("%s",a);
	scanf("%s",b);
	if(strcmp(a,b) > 0) {
		strcpy(c,a);
		strcpy(a,b);
		strcpy(b,c);
	}
	puts(a);
	puts(b);
}
