#include <stdio.h>


int main(void)
{
	char s1[100];
	char s2[100];
	int i = 0, j = 0, n = 0;

	while ((s1[i++] = getchar()) != '\n');
	i = 0;

	while (s1[i++] != '\0') {
	    if (s1[i] == '-' || s1[i] == '~' || s1[i] == '_') {
		for (; j <= s1[i+1] - s1[i-1]; j++) {
		    ++n;
		    s2[j] = (n == 1) ? s1[i-1] : s2[j-1]+1;
		}
		}
	    n = 0;
	}

	s2[j] = '\0';
	printf("%s\n", s2);
}
	
