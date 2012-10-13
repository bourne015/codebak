/*
已知在文件IN.DAT中存有100个产品销售记录，每个产品销售记录由产品代码dm(字符型4位)，产品名称mc(字符型10位)，单价dj(整型)，数量sl(整型)，金额je(长整型)五部分组成。其中：金额=单价*数量计算得出。函数ReadDat()是读取这100个销售记录并存入结构数组sell中。请编制函数SortDat()，其功能要求：
按产品名称从小到大进行排列，若产品名称相等，则按金额从小到大进行排列，最终排列结果仍存入结构数组sell中，最后调用函数WriteDat()把结果输出到文件OUT5.DAT中。
*/
#include "12.h"

int readdat(void)
{
	FILE *fd;
	int i = 0;
	pro sell[total];
	fd = fopen("product12", "r");
	if (fd == NULL) {
		printf("can't open the product file\n");
		return 0;
	}
	memset(sell, '\0', total * sizeof(pro));
	fread(&sell[i], sizeof(pro[i]), 1, fd);
	while(!feof(fd)) {
		printf("%s %s %d %d %ld\n",sell[i].code, sell[i].name,
			sell[i].price, sell[i].num, sell[i].all);
		i++;
		fread(&sell[i], sizeof(pro[i]), 1, fd);
	}
	fclose(fd);
	return 1;
}

int main(void)
{
	/*input and save some product*/
	/*if (input() == 0) {
		printf("can't create product\n");
		return 0;
	}
	*/
	/* read the product and save in sell[]*/
	readdat();

	return 1;
}



