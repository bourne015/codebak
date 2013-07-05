/*
☆题目30（整数统计排序题)
已知数据文件IN.DAT中存有200个四位数，并已调用读函数readDat()把这些数存入数组a中，请考生编制一函数jsVal()，其功能是：依次从数组a中取出一个四位数，如果该四位数连续小于该四位数以后的五个数且该数是偶数（该四位数以后不满五个数，则不统计），则统计出满足此条件的个数cnt并把这些四位数按从小到大的顺序存入数组b中，最后调用写函数writeDat( )把结果cnt以及数组b中符合条件的四位数输出到OUT.DAT文件中。
*/
#include <stdio.h>
#include <string.h>
#include <time.h>

#define all 200

int b[all];
int a[all];

int mycreate(void)
{
	int i;
	FILE *fd;
	fd = fopen("number", "w+");
	if (fd == NULL)
		return 0;
	
	for (i = 0; i < all; i++) {
		a[i] = rand()%8999+1000;
		fprintf(fd, "%d ", a[i]);
	}
	fclose(fd);
	return 1;
}

int myread(void)
{
	FILE *fd;
	int i;
	memset(a, '\0', all * sizeof(a[all]));
	fd = fopen("number", "r");
	if (fd == NULL) {
		printf("read err\n");
		return 0;
	}
	for (i = 0; i < all; i++) {
		fscanf(fd, "%d", &a[i]);
	//	fread(&a[i], sizeof(int), i, fd);
		printf("a[%d] = %d\t", i, a[i]);
	}
	printf("\n");
	fclose(fd);
	return 1;
}

int jsval(void)
{
	int i, j, flag = 0;
	int count = 0;
	for (i = 0; i < all - 5; i++) {
		for (j = i+1; j < i + 6; j++) {
			if ((a[i] < a[j]) && (a[i]%2 == 0)) 
				flag = 1;
			else {
				flag = 0;
				break;
			}
		}
		if (flag) {
			b[count] = a[i];
			printf("a[%d]: %d\n", i, a[i]);
			count++;
		}
	}
	printf("count = %d\n", count);
	for (i = 0; i < count-1; i++)
		for (j = i+1; j < count; j++) {
			if (b[i] > b[j]) {
				flag = b[i];
				b[i] = b[j];
				b[j] = flag;
			}
		}
	for (i = 0; i < count; i++)
		printf("b[%d] = %d\n", i, b[i]);
	return count;
}

void myoutput(int count)
{
	FILE *fd;
	int i;
	fd = fopen("numout", "w+");
	fprintf(fd, "total num:%d\n", count);
	for (i = 0; i < count; i++)
		fprintf(fd, "%d ", b[i]);
}
int main()
{
	int count;
	srand(time(NULL));
	if (!mycreate()) {
		printf("create err\n");
		return 0;
	}
	myread();
	count = jsval();
	myoutput(count);
	return 1;
}
