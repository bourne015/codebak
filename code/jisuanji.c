/*2012.9.27	
**fantao
**function: calculate all kinds of system, bin, oct, dec,hex
**just to make convenient for myself
*/
#include <stdio.h>
#include <math.h>
#include <string.h>

//typedef unsigned long ul;

int type = 0;
unsigned char data[32];
int num = 0; //count char number
int a[32];

void to_ten()
{
	int tmp = 0;
	int i = 0, j = 0;

	while (data[num]) {
		num++;
	}

	switch(type) {
		case 2:
			while (i < num) {
				j = data[i];
				tmp += (1<<(num-i-1))*(j-48);
				i++;
			}
			to_eight(tmp);
			to_sixteen(tmp);
			break;
		case 8:
			while (i < num) {
				tmp += (int)pow(8.0, num-i-1)*(data[i]-48);
				i++;
			}
			to_two(tmp);
			to_sixteen(tmp);
			break;
		case 10:
			while (i < num) {
				tmp += (int)pow(10.0, num-i-1)*(data[i]-48);
				i++;
			}
			to_two(tmp);
			to_eight(tmp);
			to_sixteen(tmp);
			break;
		case 16:
			while (i < num) {
				if (data[i] > 47 && data[i] < 58) 
					tmp += (int)pow(16.0, num-i-1)*
							(data[i]-48);
				else if (data[i] > 96 && data[i] < 123)
					tmp += (int)pow(16.0,num-i-1)*
							(data[i]-87);
				else if (data[i] > 64 && data[i] < 91)
					tmp += (int)pow(16.0,num-i-1)*
							(data[i]-55);
				
				i++;
			}
			to_two(tmp);
			to_eight(tmp);
			break;
		defaintt:
			printf("unknow type!!!\n");
			break;
	}
	printf("十进制  ：%d\n", tmp);
}

int jsval(int val, int to_type)
{
	int i = 0;

	memset(a, '\0', 32);

	while (val > 0) {
		a[i] = val%to_type;
		val /= to_type;
		i++;
	} 
	
	return i-1;
}
int to_two(int val)
{
	int count;
	count = jsval(val, 2);
	printf("二进制  ：");
	while (count >= 0) {
		printf("%d", a[count--]);
		if ((count+1)%4 == 0)
			printf(" ");
	}
	printf("\n");
}

int to_eight(int val)
{
	int count;
	count = jsval(val, 8);
	printf("八进制  ：");
	while (count >= 0)
		printf("%d", a[count--]);
	printf("\n");
	
}

int to_sixteen(int val)
{
	int count;
	count = jsval(val, 16);
	printf("十六进制：");
	while (count >= 0) {
		if (a[count] > 9) {
			a[count] = (char)(a[count] + 55);
			printf("%c", a[count--]);
		}
		else
			printf("%d", a[count--]);
	}
	printf("\n");

}

int main(void)
{
	int c, i;

	printf("input the type:2/8/10/16 and data\n");
	scanf("%d", &type);
	c = getchar();
	while (c != '\n' && c != ' ' && c != ':');

	memset(data, '\0', 100);
	gets(data);

	printf("ASC II  : ");	
	while (data[i] != '\0')
		printf("%d ", data[i++]);	
	printf("\n");

	to_ten();
}
