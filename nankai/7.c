/*
☆题目7（结构体操作题)
已知在文件IN.DAT中存有100个产品销售记录，每个产品销售记录由产品代码dm(字符型4位)，产品名称mc(字符型10位)，单价dj(整型)，数量sl(整型)，金额je(长整型)五部分组成。其中：金额=单价*数量计算得出。函数ReadDat()是读取这100个销售记录并存入结构数组sell中。请编制函数SortDat()，其功能要求：按产品代码从大到小进行排列，若产品代码相同，则按金额从大到小进行排列，最终排列结果仍存入结构数组sell中，最后调用函数WriteDat()把结果输出到文件OUT6.DAT中。
*/

#include <stdio.h>
#include <string.h>

#define num 100

typedef struct product
{
	char dm[4];
	char mc[10];
	int dj;
	int sl;
	long int je;
} pro;
pro sell[num];
int count;

int mycreate(void)
{
	FILE *fd;
	int i = 0;
	fd = fopen("in.dat", "w+");
	if (fd == NULL) {
		printf("can't create in.dat\n");
		return -1;
	}
	printf("please input some product:\n");
	scanf("%s", sell[i].dm);
	while (sell[i].dm[0] != '!') {
		fprintf(fd, "%s ", sell[i].dm);
	
		scanf("%s%d%d", sell[i].mc, &sell[i].dj, &sell[i].sl);
		sell[i].je = sell[i].dj * sell[i].sl;

		fprintf(fd, "%s %d %d %ld\n", sell[i].mc, sell[i].dj,
			sell[i].sl, sell[i].je);
		i++;
		scanf("%s", sell[i].dm);
	}
	
	fclose(fd);
	return 0;
}

int myread(void)
{
	FILE *fd;
	int i = 0, j;
	fd = fopen("in.dat", "r");
	if (fd == NULL) {
		printf("can't read the file\n");
		return -1;
	}
	memset(sell, '\0', sizeof(sell));

	fscanf(fd, "%s", sell[i].dm);
	while (!feof(fd)) {
		fscanf(fd, "%s%d%d%ld\n", sell[i].mc, &sell[i].dj,
			&sell[i].sl, &sell[i].je);
		i++;
		fscanf(fd, "%s", sell[i].dm);
	}

	for (j = 0; j < i; j++) {
		printf("dm:%s mc:%s dj:%d sj:%d je:%ld\n", sell[j].dm,
			sell[j].mc, sell[j].dj, sell[j].sl, sell[j].je);
	}

	printf("%d products\n", i);
	count = i;	
	fclose(fd);
	return 0;
}

int sortdat(void)
{
	int i, j;
	pro temp;
	for (j = 0; j < count-1; j++)  
	  for (i = 0; i < count-j; i++) {
		if (strcmp(sell[i].dm, sell[i+1].dm) < 0) {
			temp = sell[i];
			sell[i] = sell[i+1];
			sell[i+1] = temp;
		} else if (strcmp(sell[i].dm, sell[i+1].dm) == 0) {
			if (sell[i].je < sell[i+1].je) {
				temp = sell[i];
				sell[i] = sell[i+1];
				sell[i+1] = temp;
			}
		}
	}	
	printf("\nafter sort:\n");
	for (j = 0; j < count; j++) {
	   printf("\ndm:%s mc:%s dj:%d sj:%d je:%ld", sell[j].dm,
			sell[j].mc, sell[j].dj, sell[j].sl, sell[j].je);
	}
	printf("\n");
}

int main()
{
/*create the pro data*/
	mycreate();

/*read the pro data*/
	myread();
	
	sortdat();

	return 0;
}
