#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define total 10

int a[total];
int b[total]; //hash

int build_data(void)
{
	int i;
	int data;
	FILE *fp;

	if ((fp = fopen("DATA", "w+")) == NULL) {
		printf("create data error\n");
		return 0;
	}
	
	for (i = 0; i < total; i++) {
		data = rand()%100+899;
		fprintf(fp, "%d ", data);
	}	

	fclose(fp);
	return 1;
}
int read_data(void)
{
	FILE *fp;
	int i = 0;
	
	if ((fp = fopen("DATA", "r")) == NULL) {
		printf("create data error\n");
		return 0;
	}
	
	for (i = 0; i < total; i++) {
		fscanf(fp, "%d", &a[i]);
		printf("%d\n", a[i]);
	}	

}

int hash(void)
{
	int i;
	int c;
	for (i = 0; i < total; i++) {
		c = a[i]%10;
		while (b[c++] > 0)
			continue;
		b[--c] = a[i];
	}	
}

void test(void)
{
	int data;
	int hash_da;

	printf("input the num:");
	scanf("%d", &data)
	
	hash_da = data%10;

		
}
int main(void)
{
	build_data();
	read_data();
	hash();
	test();
}
