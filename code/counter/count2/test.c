#include <stdio.h>
#include <stdlib.h>

void ungetch(int);
int getch(void);

int getop(char s[])
{
        int i, c;
        
        while ((s[0] = c = getch()) == ' ' || c == '\t')
  	    	;
        s[1] = '\0';
        if (!isdigit(c) && c != '.')
                return c;
        i = 0;
        if (isdigit(c))
                while (isdigit(s[++i] = c = getch()))
                	;
        if (c == '.')
                while (isdigit(s[++i] = c = getch()))
			;
        s[i] = '\0';

	if (c != EOF)
		ungetch(c);

 //       return NUMBER;
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

int main(void)
{
	char s[100];
	int i = 0;
	double k;

	getop(s);
		
	while (s[i]) {
		printf("%c---", s[i]);
		printf("%d\n", s[i++]);
	}

//	printf("no atof: %f\n", s);
	printf("atof: %f\n", atof(s));

	if (isdigit(s[0]))
		printf("digit\n");
	else 
		printf("sign\n");
}
