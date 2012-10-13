/*
★☆题目14（整数统计排序题)
已知数据文件IN.DAT中存有200个四位数，并已调用读函数readDat()把这些数存入数组a中，请考生编制一函数jsVal()，其功能是：依次从数组a中取出一个四位数，如果该四位数连续大于该四位数以后的五个数且该数是奇数（该四位数以后不满五个数，则不统计），则统计出满足此条件的个数cnt并把这些四位数按从小到大的顺序存入数组b中，最后调用写函数writeDat( )把结果cnt以及数组b中符合条件的四位数输出到OUT.DAT文件中。
*/

#include "14.h"

void jsval(void)
{
	int i, j, temp;
	int flag = 0;
	for (i = 0; i < all-1; i++) {
		printf("a[%d]= %d\n", i, a[i]);
		for (j = i+1; j < i+6; j++) {
			if ((a[i] > a[j]) && (a[i]%2 != 0))
				flag = 1;
			else flag = 0;
		}
		if (flag == 1) {
			b[count] = a[i];
			count++;
		}
	}
	printf("count=%d\n", count);
	for (j = 0; j < count; j++) {
		for (i = 0; i < count-1; i++) {
			if (b[i] > b[i+1]) {
				temp = b[i];
				b[i] = b[i+1];
				b[i+1] = temp;
			}
		}
	}
	for (j = 0; j < count; j++)
		printf("b[%d]= %d\n", j, b[j]);
}

int readdat(void)
{
	FILE *fd;
	int i = 0;
	fd = fopen("in.dat", "r");	
	if (fd == NULL) {
		printf("failed to open file\n");
		return -1;
	}
	
	while (!feof(fd)) {
		fread(&a[i++], sizeof(int), 1, fd);
	//	printf("a[%d]= %d\n", i++, a[i]);
	}
	
	fclose(fd);
	return 1;
}

int main()
{
	//int res;
	srand(time(NULL));
	if (mycreate() == -1) {
		printf("failed to create number\n");
		return -1;
	}
	/*read the data*/
	readdat();
	
	/*compare the data*/
	jsval();

	return 1;
} 
