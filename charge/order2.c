#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char *s = "abcdefg";
	char *h, *head;
	int len;

	h = malloc(sizeof(10));
	head = h;
	if (h == NULL) {
		return -1;
	}

	len = strlen(s) - 1;
	while (*(h++) = *(s+len) ) {
		len--;
	}
	printf("h:%s\n", head);
}
