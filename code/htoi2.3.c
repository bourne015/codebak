#include <stdio.h>
#include <math.h>

int main(void)
{
	char a[10], *p;
	int i = 0, sum = 0;
	while ((a[i++] = getchar()) != '\n');
	p = a;

	while (*p == '0' || *p == 'x' || *p == 'X')
		++p;
	i = 0;
	while (*p != '\n')
		a[i++] = *(p++);				
	a[i] = '\0';

	p = a;
//	printf("%s\n", p);
	while (*p != '\0') {
		if (*p >= '0' && *p <= '9')
			sum += (*p - 48) * (int)pow(16, i-1);
		else if (*p >= 'A' && *p <= 'Z')
			sum += (*p - 55) * (int)pow(16, i-1);
		else if (*p >= 'a' && *p <= 'z')
			sum += (*p - 87) * (int)pow(16, i-1);
		--i;
		++p;	
	}
	printf("%d\n", sum);
}
