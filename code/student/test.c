#include <stdio.h>

int main(void)
{
	int a[10];
	int i = 0;
	int j = 0;
	do {
		scanf("%d", &a[i]);
	} while (a[i++] != 0 && i < 10);

	i = 0;
	while (a[i] != 0) {
		printf("%d\n", a[i]);
		i++;
	}
}
