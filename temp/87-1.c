#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void main(void)
{	
	FILE *fp;
	int min=1000,max=1010;
	int i;
	int num;
	if((fp=fopen("87-1.txt","w"))==NULL) {
		printf("open error\n");
		exit(1);
	}
	printf("opend\n");
	srand((unsigned int)time(NULL));
	for(i=0; i<=max-min; i++) {
		num=min+rand()%(max-min+1);
		printf("%d  ",num);
		fputc(num,fp);
		//fwrite(&num,sizeof(int),1,fp);
	}
	fclose(fp);
	printf("writed successed\n");
	if((fp=fopen("87-1.txt","r"))==NULL) {
		printf("open error\n");
		exit(1);
	}
	while((num=fgetc(fp))!=EOF) {
	//while(!feof(fp)) {
	//	fread(&num,sizeof(int),1,fp);
		fputc(num,stdout);
		//printf("%d\n",num);
	}
	fclose(fp);
}
