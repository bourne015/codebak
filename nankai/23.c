/*
*********************************************************************
题目23 (实数运算题)
已知在文件in.dat中存有N个（个数<200）实数，函数readdat()读取这N个实数并存入数组xx中。请编制函数calvalue()，其功能要求：
1、求出这N个实数的平均值aver；
2、分别求出这N个实数的整数部分之和sumint以及小数部分之和sumdec，最后调用函数writedat()把所求的结果输出到文件out.dat中。
*/

#include <stdio.h>

int main()
{
	double i = 23.345;
	double dec;
	int n = 0, sumdec = 0;
	dec = i - (int)i;
	printf("%lf\n", dec);
	while (dec > 0 && dec < 1) {
		n = (int)(dec * 10);
	printf("dec = %lf\t", dec);
	printf("n = %d\n", n);
		sumdec += n;
		dec = dec*10 - n;
	}
	printf("%d\n", sumdec);
}
