#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int a[10];
	int k = 50;
	int i = 0;

	do {
		scanf("%d", &a[i++]);
	} while (a[--i] != '\n');

	i = 0;
	while (a[i] != '\n') {
		printf("%d\n", a[i]);
		i++;
	}
}
