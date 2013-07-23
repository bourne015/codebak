#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data {
	int a;
	struct data *next;
};

int main(void)
{
	int i = 0;
	struct data *head, *p, *p2;

	p = malloc(sizeof(struct data));
	head = p;
	for (i = 1; i < 2; i++) {
		p->a = i;
		p2 = malloc(sizeof(struct data));
		p->next = p2;
		p =p2;
	}

	while (head->next != NULL) {
		printf("%d ", head->a);
		head = head->next;
	}

	free(p);
	return 0;
}
