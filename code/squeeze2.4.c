#include <stdio.h>
#include <string.h>

void delet(char *s1, char *s2)
{
	char *s = s1;
	int i = 0, j = 0;
	while (s1[i] != '\0') {
		for (j = 0; s2[j] != '\0'; j++) {
			if (s1[i] == s2[j])
				s1[i] = '*';
		}
	i++;
	}

	printf("%s\n", s);	
}

int main(void)
{
	char s1[] = "hello hand";
	char s2[] = "ha";

	delet(s1, s2);

	return 0; 
}
