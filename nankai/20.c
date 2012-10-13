/*
*★题目20（Fibonacci数列题)
*编写函数jsValue，它的功能是：求Fibonacci数列中大于t的最小的一个数，结果由函数返回。其中Fibonacci数列F(n)的定义为：
*    F(0)=0,F(1)=1
*    F(n)=F(n-1)+F(n-2)
*   最后调用函数writeDat()读取50个数据t，分别得出结果且把结果输出到文件out.dat中。
*    例如：当t=1000时，函数值为：1597.*
*/

#include <stdio.h>
#include <stdlib.h>

int jsvalue(int *fb, int t)
{
	int i;
	fb[0] = 0;
	fb[1] = 1;
	for (i = 2; ; i++) {
		fb[i] = fb[i - 1] + fb[i -2];
		if (fb[i] > t) 
			return fb[i];
	}
	return 0;	
}

int main()
{
	int t, *fb;
	int result;
	printf("please input a number: ");
	scanf("%d", &t);
	fb = (int *)malloc((t + 1) * sizeof(int));
	
	result = jsvalue(fb, t);
	
	if (result) {
		printf("the result is :%d\n", result);
	} else {
		printf("can't find the data\n");
	}

	return 1;	
}
