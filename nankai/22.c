/*
*★题目22（平方根问题)
*请编写函数countValue()，它的功能是：求n以内（不包括n）同时能被3与7整除的所有自然数之和的平方根s，并作为函数值返回，最后结果s输出到文件out.dat中。
*    例如若n为1000时，函数值应为：s=153.909064。
*/

#include <stdio.h>
#include <math.h>

double countvalue(int n)
{
	int i, sum = 0;
	double result;
	
	for (i = 0; i < n; i++) {
		if (i%3 == 0 && i%7 == 0) sum += i;
	}
	result = sqrt(sum);

	return result;
}

int main()
{
	
	int n;
	double result;
	
	printf("please input a number:\n");
	scanf("%d", &n);
	
	result = countvalue(n);
	printf("the result is :%lf\n", result);
	
	return 0;
}
