/*
★题目57（出圈题）
(本题采用实际上机题，05年9月和04年9月实际上机题与下面相同)
    设有n个人围坐一圈并按顺时针方向从1到n编号,从第s个人开始进行1到m的报数, 报数到第m个人, 此人出圈, 再从他的下一个人重新开始1到m的报数,如此进行下去直到所有的人都出圈为止。现要求按出圈次序,给出这n个人的顺序表p。请考生编制函数Josegh()实现此功能并调用函数WriteDat()把编号按照出圈的顺序输出到OUT.DAT文件中。
注意：第1个出圈的编号存放在p[0]中,第2个出圈的编号存放在p[1]中,直至第n个出圈的编号存放在p[n-1]中。
    设 n = 100, s = 1, m = 10进行编程。
*/

#include <stdio.h>

#define n 100
#define s 1
#define m 10

int main(void)
{
	int i = 0, j = 0;
	int p[n], all[n];
	int leave = n;
	int count = 0;

	for (i = 0; i < n; i++) {
		p[i] = 0;
		all[i] = 0;
	}
	while (leave != 0) {
		for (i = 0; i < n; i++) {
			count++;
			if (all[i] == 1) {
				count--;
				continue;
			} else if (count%m == 0) {
				p[j++] = i+1;
				all[i] = 1;
				leave--;
			}
		}
	}

	for (i = 0; i < n; i++)
		printf("p[%d] = %d\n", i, p[i]);
}
