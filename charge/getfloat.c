#include <stdio.h>

int getfloat(float *pn)
{
	int c, sign;
	float c2, lit;
	
	while (isspace(c = getch()))
		;
	if (!isdigit(c) && c != EOF &&
		c != '-' && c != '+' && c != '.') {
		ungetch(c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();
//	while (!isdigit(c))
//		c = getch();
	if (isdigit(c))
		for (*pn = 0; isdigit(c); c = getch()) {
			*pn = 10 * *pn + (c - '0');
		}
	if (c = '.')
		c2 = getch();
		for (; isdigit(c2); c2 = getch()) {
		
		}
				
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return *pn;
}

#define bufsize 100

int bufp[bufsize];
int buf = 0;

int getch()
{
	return ((buf > 0) ? bufp[--buf] : getchar());
}

void ungetch(int c)
{
	if (buf >= bufsize)
		printf("err\n");
	else
		bufp[buf++] = c;
}

int main(void)
{
	float c;
	c = getfloat(&c);
	printf("c:%f\n", c);
}
