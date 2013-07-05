#include <stdio.h>
#include <string.h>

int main(void)
{
	char s[] = "abcd";
	int i = 0, j = 0;
	char tmp;

	i = strlen(s) - 1;
	printf("%d\n", i);

	for (; j < i;j++, i--) {
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
	}
i = 0;
while (s[i])	
	printf("%c\n", s[i++]);
}
