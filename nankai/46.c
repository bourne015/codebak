/*
☆题目46（数字统计排序题 ）
已知数据文件IN.DAT中存有200个四位数，并已调用读函数readDat()把这些数存入数组a中，请考生编制一函数jsVal()，其功能是：依次从数组a中取出一个四位数，如果该四位数连续大于该四位数以前的五个数且该数是奇数，且该数必须能被7整除（该四位数以前不满五个数，则不统计），则统计出满足此条件的个数cnt并把这些四位数按从大到小的顺序存入数组b中，最后调用写函数writeDat( )把结果cnt以及数组b中符合条件的四位数输出到OUT.DAT文件中。
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define total 2000

int a[total];
int b[total];
int cnt = 0;

int create(void)
{
	int b[total];
	FILE *fp;
	int i;

	fp = fopen("IN.DAT", "w+");
	if (fp == NULL) {
		printf("create file err\n");
		return 0;
	}

        for (i = 0; i < total; i++) {
                b[i] = rand()%1000+8999;
                fprintf(fp, "%d ", b[i]);
//		printf("b[%d] = %d\n", i, b[i]);
        }
	fclose(fp);
	return 1;
}

int readdat()
{
	FILE *fp;
	int i;

	fp = fopen("IN.DAT", "r");
	if (fp == NULL) {
		printf("read err\n");
		return 0;
	}

	for (i = 0; i < total; i++) {
		fscanf(fp, "%d ", &a[i]);
//		printf("a[%d] = %d\n", i, a[i]);
	}
	fclose(fp);
	return 1;
}

void jsval()
{
	int i, j;
	int flag = 0;

	for (i = 5; i < total; i++) {
		if (a[i]%2 != 0 && a[i]%7 == 0) {
			for (j = i-5; j < i; j++){
				if(a[i] > a[j]) {
					flag = 1;
				 } else {
					flag = 0;
					break;
				}
			}

		if (flag)
			b[cnt++] = a[i];
			
		}	
	}
	for (i = 0; i < cnt-1; i++)
		for (j = i; j < cnt-1; j++)
			if (b[i] < b[j]) {
				flag = b[j];
				b[j] = b[i];
				b[i] = flag;
			}
}

void writedat(void)
{
	FILE *fp;
	int i;

	fp = fopen("OUT.DAT", "w");
	if (fp == NULL) {
		printf("failure to create OUT.DAT");
		return;
	}
	fprintf(fp, "%d\n", cnt);
	for (i = 0; i < cnt; i++) {
		fprintf(fp, "b[%d]=%d\n", i, b[i]);
	}
	fclose(fp);
}
int main(void)
{
	if (!create())
		return 0;
	if (!readdat())
		return 0;
	jsval();

	writedat();
}

