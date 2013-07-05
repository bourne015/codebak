#include <stdio.h>

int main()
{
	char a[] = "fan";
	char b[] = "123";

	printf("c-f %d\n", atof(a));
	printf("c-i %d\n", atoi(a));
	printf("n-f %d\n", atof(b));
	printf("n-i %d\n", atoi(b));
}
