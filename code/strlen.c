#include <stdio.h>

#define MAX 100

unsigned int my_strlen(char *str)
{
	unsigned int count = 0;
	while (*(str++))
		count++;

	printf("%u\n", count);
	return count;
}

int main(void)
{
	char str[MAX];
	
	gets(str);

	my_strlen(str);
}
