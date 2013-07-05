#include <stdio.h>
#include <stdlib.h>


typedef struct str
{
	int data;
	struct str *next;
} *stu;

void display(stu head);
stu revert(stu head);

int main()
{
	stu p, p2, head;
	int i = 0;

	p = malloc(sizeof(stu));
	if (p == NULL) return -1;
	p->data = i++;
	head = p;
	for (;i < 10; i++) {
		p2 = p;
		p = malloc(sizeof(stu));
		if (p == NULL) return -1;
		p->data = i;
		p2->next = p;
	}
	
	p->next = NULL;
	display(head);
	head = revert(head);
	display(head);
	free(p);
}

stu revert(stu head)
{
	stu p1, p2, p3;
	p1 = head;
	
	p2 = p1->next;
	while (p2 != NULL) {
		p3 = p2->next;
		p2->next = p1;
		p1 = p2;
		p2 = p3;
	}
	
	head->next = NULL;
	return p1;
}

void display(stu head)
{
	while (head != NULL) {
		printf("p: %d\n", head->data);
		head = head->next;
	}
}
