#include <stdio.h>

#define MAX 100

void mystrcat(char *s, char *t)
{
	char *p = s;
	while (*(s++) != '\0')
		;
	s--;
	while (*t != '\0')
		*(s++) = *(t++);

	*s = '\0';
//	printf("%s\n", p);
}

int main(void)
{
	char s[MAX];
	char t[MAX];
	gets(s);
	gets(t);

	mystrcat(s, t);
	printf("%s\n", s);
}
