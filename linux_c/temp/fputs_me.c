#include <stdio.h>

#define max 4

int main()
{
	char buf[max];
	while (fgets(buf, max, stdin) != NULL)
		if (fputs(buf, stdout) == EOF)
			printf("output error\n");
	if (ferror(stdin))
		printf("input error\n");
	exit(0);
}
