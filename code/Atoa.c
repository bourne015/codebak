#include <stdio.h>

int main(void)
{
	int i = 0;
	char a[20];
	while ((a[i++] = getchar()) != '\n');
	i = 0;
	while (a[i] != '\0') {
		a[i] = (a[i] >= 'A' && a[i] <= 'Z') ? (a[i] + 32) : a[i];
		i++;
	}

	printf("%s\n", a);
}
