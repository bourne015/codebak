#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char buf[100];
	gets(buf);
	printf("%d\n", atoi(buf));
}
