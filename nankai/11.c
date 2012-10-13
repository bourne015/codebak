/*
把 s 字符串中的所有字母改写成该字母的下一个字母，字母z改写成字母a。要求大写字母仍为大写字母，小写字母仍为小写字母，其它字符不做改变。
    请考生编写函数chg(char *s)实现程序要求，最后调用函数readwriteDAT( )把结输出到文件bc1.out中。
  例如：s 字符串中原有的内容为：Mn.123Zxy，则调用该函数后，结果为：No.123Ayz。
*/
#include<stdio.h>
#include<string.h>
#define n 80

chg(char *s)
{
	//int i;
	while (*s != '\0') {
		if ((*s >='a'&& *s < 'z') || 
			(*s >= 'A' && *s < 'Z'))
			(*s)++;
		else if (*s == 'z' || *s == 'Z')
			*s = *s - 25;
		s++;
	}
}

void main(void)
{
	char a[n];
	printf("input a string: ");
	gets(a);
	printf("you string is: ");
	puts(a);
	chg(a);
	printf("now the string is: ");
	puts(a);
	printf("\n");
}

