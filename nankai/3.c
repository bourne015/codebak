/******************************************************************************
函数ReadDat( )实现从文件IN.DAT中读取一篇英文文章存入到字符串数组xx中；请编制函数StrOR( )，其函数的功能是：以行为单位依次把字符串中所有小写字母o左边的字符串内容移到该串的右边存放，然后把小写字母o删除，余下的字符串内容移到已处理字符串的左边存放，之后把已处理的字符串仍按行重新存入字符串数组xx中。最后main()函数调用函数WriteDat()把结果xx输出到文件OUT5.DAT中。
*********************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define rank 10
#define file 80
char xx[rank][file];
int maxline = 0;

int main(void)
{
	if (!readdat()) {
		printf("err, can't in.dat\n");
		return 0;
	}
	stror();
	writedat();
	return 1;
}

int stror(void)
{
	int i = 0, j = 0, n = 0;
	char *p, b[rank][file];
	for (j = 0; j < maxline; j++, i = 0) {
		while (xx[j][i] != 'o') {
			b[j][i] = xx[j][i];
			i++;
		}
		b[j][i] = '\0';
		printf("xx[%d]=%s\n", j, xx[j]);
		printf("b[%d]=%s\n\n", j, b[j]);
	}
	for (j = 0, i = 0; j < maxline; j++) {
		strcat(xx[j], b[j]);
	/*	while (xx[j][i] != 'o') 
			i++;
		for (n = 0; xx[j][i] != '\0'; i++, n++) {
			//xx[j][n] = xx[j][i];
		}
	*/
	printf("xx[%d]=%s\n", j, xx[j]);
	}
	return 0;
}

int writedat(void)
{
	FILE *fd;
	int i;
	fd = fopen("out.dat", "w");
	if (fd == NULL) {
		printf("err, can't open out.dat\n");
		return 0;
	}
	for (i = 0; i < maxline; i++) {
		fprintf(fd, "%s\n", xx[i]);
	}
	fclose(fd);
	return 1;
}

int readdat(void)
{
	FILE *fd;
	int i;
	fd = fopen("english.dat", "r");
	if (fd == NULL)
		return 0;
	while (fgets(xx[i], 80, fd) != NULL) {
	//	printf("line%d:%s\n\n", i, xx[i]);
		i++;
	}
	maxline = i;
	fclose(fd);
	return 1;
}
