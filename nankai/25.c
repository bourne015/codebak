/*
★题目25 （回文数问题）
下列程序的功能是：寻找并输出11至999之间的数m，它满足m,m2和m3均为回文数。所谓回文数是指其各位数字左右对称的整数，例如121，676，94249等。满足上述条件的数如m=11,m2=121,m3=1331皆为回文数。请编制函数int svalue(long m)实现此功能，如果是回文数，则函数返回1，反之则返回0。最后把结果输出到文件out.dat中。
*/

#include <stdio.h>

int svalue(int m)
{
	int n = m;
	int i = 0;
	while (m != 0) {
		i = i*10 + m%10;
		m = m/10;
	}
	if (i == n) return 1;
	else return 0;	
}

int main()
{
	int i, m;
	FILE *fd;

	fd = fopen("out.dat", "w");
	if (fd == NULL) {
		printf("can't open out.dat\n");
		return -1;
	}

	for (i = 11; i < 1000; i++) {
		if (svalue(i) && svalue(i * i) &&
			svalue(i * i * i)) {
			printf("i=%d i*i=%d i*i*i=%d\n", i, i*i, i*i*i);
			fprintf(fd, "%d %d %d\n", i, i*i, i*i*i);
		}
	}

	fclose(fd);
	return 1;
}
