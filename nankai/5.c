/*
在文件in.dat中有200个正整数，且每个数均在1000至9999之间。函数ReadDat()读取这200个数存放到数组aa中。请编制函数jsSort()，其函数的功能是：要求按每个数的后三位的大小进行升序排列，然后取出满足此条件的前10个数依次存入数组bb中，如果后三位的数值相等，则按原先的数值进行降序排列。最后调用函数WriteDat()把结果bb输出到文件out.dat中。
    例：处理前 6012 5099 9012 7025 8088
        处理后 9012 6012 7025 8088 5099
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define max 20
#define num 10
int a[max], b[num];

int readdat(void)
{
	FILE *fd;
	int i;
	fd = fopen("in.dat", "r");
	if (fd == NULL) {
		printf("err, can't open in.dat\n");
		return 0;
	}
	for (i = 0; i < max; i++) {
		fread(&a[i], sizeof(int), 1, fd);
		printf("the priame is:%d  ",a[i]);
	}
	printf("\n");
	fclose(fd);
	return 1;
}

void jssort(void)
{
	int i, j, t;
	for (j = 0; j < (max - 1); j++)
	for (i = 0; i < (max - 1); i++) {
		if (a[i]%1000 > a[i+1]%1000 || a[i]%1000 == a[i+1]%1000
			&& a[i] < a[i+1]) {
			t = a[i];
			a[i] = a[i+1];
			a[i+1] = t;
		}
	}
	for (j = 0; j < num; j++) {
			b[j] = a[j];
			printf("fnow is: %d\n",b[j]);
		}
	
	//printf("\n");
}

int writedat(void)
{
	FILE *fd;
	int i;
	fd = fopen("out.dat", "w");
	if (fd == NULL) {
		printf("errno,can't creat out.dat\n");
		return 0;
	}
	for (i = 0; i < num; i++) {
		fwrite(&b[i], sizeof(int), 1, fd);
		//printf("fnow is: %d\n",b[i]);
	}
	fclose(fd);
	return 1;
}

int display(void) 
{
	FILE *fd;
	int i, b2[num];
	fd = fopen("out.dat", "r");
	if (fd == NULL) {
		printf("errno, can't open out.dat\n");
		return 0;
	}
	for (i = 0; i < num; i++) {
		fread(&b2[i], sizeof(int), 1, fd);
		printf("now is: %d\n", b2[i]);
	}
	printf("\n");
	fclose(fd);
}

int main(void)
{
	FILE *fd;
	int i,new[max];
	srand(time(NULL));
	for (i = 0; i < max; i++)
		new[i] = rand()%9000+1000;
	fd = fopen("in.dat","w");
	if (fd == NULL ) {
		printf("err, can't creat int.dat\n");
		return 0;
	}
	for (i = 0; i < max; i++)
		fwrite(&new[i], sizeof(int), 1, fd);
	fclose(fd);
	readdat();
	jssort();
	writedat();
	display();
	return 1;
}
