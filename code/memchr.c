#include <stdio.h>

#define MAX 100
#define count 10

char *my_memchr(char *buf, char ch, int n)
{
	for (; *buf != '\0' && n > 0; buf++, n--) {
		if (*buf == ch)
			return buf;
			//break;
	}

//	printf("%s\n", buf);
	return 0;
}

int main(void)
{
	char buf[MAX];
	char ch;
	char *location;

	gets(buf);
	ch = getchar();	

	location = my_memchr(buf, ch, count);	
	
	printf("%s\n", location);
}
