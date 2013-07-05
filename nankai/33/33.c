/*
★☆题目33（方差运算题)
请编制函数ReadDat()实现从文件IN.DAT中读取1000个十进制整数到数组xx中；请编制函数Compute()分别计算出xx中偶数的个数even，奇数的平均值ave1，偶数的平均值ave2以及方差totfc的值，最后调用函数WriteDat()把结果输出到OUT.DAT文件中。
    计算方差的公式如下：
             N             2
    totfc=1/N∑(xx[i]-ave2)
             i=1
    设N为偶数的个数，xx[i]为偶数，ave2为偶数的平均值。
    原始数据文件存放的格式是：每行存放10个数，并用逗号隔开。（每个数均大于0且小于等于2000）
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 4

int xx[MAX];

int mycreate(void)
{
	FILE *fd;
	int i;
	for (i = 0; i < MAX; i++) {
		xx[i] = rand()%32767;
		printf("%d\n", xx[i]);
	}
}

int compute(void)
{
	int even1 = 0, sum1 = 0, aver1;
	int even2 = 0, sum2 = 0, aver2;
	int i, sumtot = 0, totfc;
	for (i = 0; i < MAX; i ++) {
		if (xx[i]%2 == 0) {
			even1++;
			sum1 += xx[i];
		} else {
			even2++;
			sum2 += xx[i];
		}
	}
	aver1 = sum1/even1;
	aver2 = sum2/even2;

	for (i = 0; i < MAX; i++)
		sumtot += (xx[i] - aver1) * (xx[i] - aver1);
	totfc = sumtot/MAX;

	printf("even1 = %d sum1 = %d aver1 = %d\n", even1, sum1, aver1);
	printf("even2 = %d sum2 = %d aver2 = %d\n", even2, sum2, aver2);
	printf("totfc = %d\n", totfc);
}

int main(void)
{
	srand(time(NULL));
	mycreate();
	compute();
}
