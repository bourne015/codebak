#include <stdio.h>

#define MAX 100

char *my_strstr(char *str1, char *str2)
{
	int flag = 0;
	char *t1 = str1, *t2 = str2;
	char *first;
	for (t1 = str1; *t1 != '\0'; t1++) {
		for (t2 = str2; *t2 != '\0'; t1++, t2++) {
			if (*t1 == *t2) {
				first = t1;
				flag = 1;
			} else {
				flag = 0;
				break;
			}
		}
		if (flag)
			return --first;
	}
	return NULL;
}

int main(void)
{
	char str1[MAX], str2[MAX];
	char *location;

	gets(str1);
	gets(str2);

	location = my_strstr(str1, str2);

	printf("%s\n", location);
}
