#include<stdio.h>
#include<stdlib.h>
void main()
{
	FILE *f1,*f2;
	int i,ch;
	int a[7],b[7];
	f1=fopen("file1","r");
	f2=fopen("file2","w");
//	fread(a,sizeof(int),5,f1);
//	fwrite(a,sizeof(int),5,f2);
	while((ch=fgetc(f1))!=EOF) {
		fputc(ch,f2);
	}
	fread(b,sizeof(int),5,f2);
	for(i=0;i<5;i++)
		printf("%d\n",b[i]);
	fclose(f1);
	fclose(f2);
}
