#include<stdlib.h>
#include<stdio.h>
void main()
{
        FILE *fp;
       	int j,i;
	int b[7],a[7];
	 if((fp=fopen("file1","w"))==NULL) {
                printf("open error\n");
                exit(1);
        }
        for(i=0; i<5; i++) {
                scanf("%d",&a[i]);
        }
                fwrite(a,sizeof(int),5,fp);
        fclose(fp);
        if((fp=fopen("file1","r"))==NULL) {
                printf("open error\n");
                exit(1);
	}
	fread(b,sizeof(int),5,fp);
	for(i=0; i<5; i++)
		printf("%d\n",b[i]);
//		fputc(b[i],stdout);
	fclose(fp);

}

