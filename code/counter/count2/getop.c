#include "common.h"

int getop(char s[])
{
	static int count = 0;
        int i = 0;
	char c;
printf("count:%d\n", count);
	if (count == 0)        
		to_polan(output);
while (output[i])
printf("out:%c ", output[i++]);
while (1);
	if (output[count] == '\0')
		return EOF;

        while ((c = s[0] = output[count]) == ' ' || c == '\t')
  	    	count++;
        s[1] = '\0';
        if (!isdigit(c) && c != '.')
	{
		count++;
                return c;
	}
        i = 0;
        if (isdigit(c))
                while (isdigit(c = s[i++] = output[count++]))
			if (c = '\n')
				goto one;
        if (c == '.')
                while (isdigit(c = s[i++] = output[count++]))
			if (c = '\n')
				goto one;
	s[--i] = '\0';
	count--;
	return NUMBER;
one:
        s[--i] = '\0';
//	count--;
printf("s:%s\n", s);
printf("end count:%d\n",count);
        return NUMBER;
}

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
