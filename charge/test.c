#include <stdio.h>
#include <string.h>

int main()
{
	int a;
	unsigned int aa;
	char b;
	unsigned char bb;
	float c;
	long d;
	unsigned long dd;
	double long ddd;

	printf("int %lu\n", sizeof(a));
	printf("uns int %lu\n", sizeof(aa));
	printf("char %lu\n", sizeof(b));
	printf("char %lu\n", sizeof(bb));
	printf("float %lu\n", sizeof(c));
	printf("long%lu\n", sizeof(d));
	printf("uns long%lu\n", sizeof(dd));
	printf("double long%lu\n", sizeof(ddd));
}
