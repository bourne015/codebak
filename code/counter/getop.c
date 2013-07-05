#include "common.h"

int getop(char s[])
{
        int i, c;
        
        while (s[i] == ' ' || s[i] == '\t')
		i++;
       // s[i] = '\0';
        if (!isdigit(s[i]) && s[i] != '.')
                return s[i];
        i = 0;
        if (isdigit(s[i]))
                while (isdigit(s[++i])
                	;
        if (c == '.')
                while (isdigit(s[++i])
			;
        s[i] = '\0';

	if (c != EOF)
		ungetch(c);

        return NUMBER;
}
/*
#define BUFSIZE	100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many char\n");
	else
		buf[bufp++] = c;
}
*/
