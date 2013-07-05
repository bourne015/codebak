#include <stdio.h>

#define MAX 1024
#define N 3

void mystrncpy(char *s, char *t, int n)
{
	while ((*(s++) = *(t++))) {
		if (--n <= 0)
			break;
	}
	*s = '\0';
}

int main(void)
{
	char s[MAX];
	char t[MAX];

	gets(t);

	mystrncpy(s, t, N);
	
	printf("%s\n", s);
}
