#include <stdio.h>

#define MAX 100
#define N 3

int mystrncmp(char *s, char *t, int n)
{
	for (; *s != '\0' && n-- > 0; s++, t++) {
		if (*s == *t)
			continue;
		else
			return (*s - *t);
	}

	if (*t != '\0')
		return (-*t);
	else 	
		return 0;
}

int main(void)
{
	char s[MAX];
	char t[MAX];
	int res;

	gets(s);
	gets(t);

	res = mystrncmp(s, t, N);

	printf("%d\n", res);
}
