#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main()
{
	FILE *s;
	int c;
	if(s=fopen("test.txt","w+")==NULL) {
		printf("open error\n");
		exit(1);
	}
	while((c=fgetc(stdin))!='*') {
		fputc(c,s);
	//printf("there\n");
	}
//	fclose(s);
}
