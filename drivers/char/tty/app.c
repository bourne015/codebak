#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	FILE *fp;
	char buff[] = "it's buffer";
	char buff2[] = "replaced";

	fp = fopen("gprs_uart", "w");
	if (fp == NULL) {
		printf("error\n");
		return 0;
	}

	fwrite(buff, sizeof(buff), 1, fp);

	printf("now writed \n");
	
	strcpy(buff, buff2);
	printf("now buff:%s\n", buff);	
	fread(buff, sizeof(buff), 1, fp);

	printf("after read, buff:%s\n", buff);	
	
	return 1;
}
