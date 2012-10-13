/*
题目50（字符串左右排序交换题 ）
函数ReadDat()实现从文件in.dat中读取20行数据存放到字符串数组xx中（每行字符串长度均小于80）。请编制函数jsSort()，其函数的功能是：以行为单位对字符串按给定的条件进行排序，排序后的结果仍按行重新存入字符串数组xx中，最后调用函数WriteDat()把结果xx输出到文件out.dat中。
　　条件：从字符串中间一分为二，左边部分按字符的ASCII值升序排序，排序后左边部分与右边部分进行交换。如果原字符串长度为奇数，则最中间的字符不参加处理，字符仍放在原位置上。
　　例如：位置　　　0　1　2　3　4　5　6　7　8
　　　　　源字符串　d  c  b  a  h  g  f  e 
                    4  3  2  1  9  8  7  6  5
    则处理后字符串  h  g  f  e  a  b  c  d
                    8  7  6  5  9  1  2  3  4
*/

#include <stdio.h>
#include <string.h>

#define BUF 100

void sort(char buf[BUF])
{
	int i, j, temp;
	int half, lon;
	lon = strlen(buf);
	half = lon/2;
//	printf("%d\n", half);
	for (i = 0; i < half-1; i++)
		for (j = i+1; j < half; j++) {
			if (buf[i] > buf[j]) {
				temp = buf[j];
				buf[j] = buf[i];
				buf[i] = temp;
			}
		}
//	printf("%s\n", buf);
	for (i = half-1, j = lon-1; i >= 0; j--, i--) {
		temp = buf[i];
		buf[i] = buf[j];
		buf[j] = temp;
	}
	printf("%s\n", buf);
}

int main(void)
{
	char buf[BUF];
	int i;

	while ((buf[i++] = getchar()) != '\n');
	buf[--i] = '\0';
//	printf("%s\n", buf);

	sort(buf);
}
