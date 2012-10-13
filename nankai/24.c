/*
*题目24（完全平方数问题)
*下列程序prog1.c的功能是：在三位整数（100至999）中寻找符合条件的整数并依次从小到大存入数组中；它既是完全平方数，又是两位数字相同，例如144、676等。
*    请编制函数实现此功能，满足该条件的整数的个数通过所编制的函数返回。
*/

#include <stdio.h>
#include <math.h>

int comp(int i)
{
	int data, ten, hum;
	data = i%10;
	ten = (i/10)%10;
	hum = i/100;
	if (data == ten || data == hum || ten == hum)
		return 1;
	else 
		return 0;
}

int main()
{
	int j = 0, b[15];
	int i, sq;
	for (i = 100; i < 1000; i++) {
		sq = sqrt(i);
		if (sq * sq == i)
			if (comp(i)) { 
				b[j++] = i;
			}
	}
	for (i = 0; i < j; i++)
		printf("b[%d]= %d\n", i, b[i]);
}

