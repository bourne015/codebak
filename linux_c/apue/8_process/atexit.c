#include <stdio.h>
#include <stdlib.h>

void func1(void)
{
	printf("this is exit 1\n");
}

void func2(void)
{
	printf("this is exit 2\n");
}

void func3(void)
{
	printf("this is exit 3\n");
}
int main(void)
{
	if (atexit(func1) != 0)
		printf("atexit1 error\n");
	if (atexit(func2) != 0)
		printf("atexit2 error\n");
//	return 0;
	if (atexit(func3) != 0)
		printf("atexit3 error\n");

//	return 0;
}
