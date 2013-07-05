//P75 4-13
#include <stdio.h>
#include <string.h>

int reverse(char *a, char m[], int i)
{
//	int i = 0;
	if (*a != '\0') {
		reverse(a+1, m, i+1);
		m[4-i] = *a;
	}
}

int main(void)
{
	char s[] = "abcde";
	char m[100];
int i = 0;
	reverse(s, m, 0);
	while (m[i])
		printf("%c", m[i++]);
	printf("\n");
}
