#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tree {
	int elemt;
	struct tree *left;
	struct tree *right;
	int hight;
};

int i = 0;
struct tree *dat, *head;

struct tree *insert(struct tree *p, int x)
{
	if (p == NULL) {
		p = malloc(sizeof(struct tree));
		p->elemt = x;
		p->left = NULL;
		p->right = NULL;

		if (i++ == 0) head = p;
	}
	else if (p->elemt > x) {
		p->left = insert(p->left, x);
	}
	else if (p->elemt <= x) {
		p->right = insert(p->right, x);
	}
	
	return p;
}

void display(struct tree *p)
{
	//if (p != NULL) {
	//	display(p->left);
		printf("%d ", p->elemt);
	//	display(p->right);
	//}
	p = p->left;
		printf("%d ", p->elemt);
}

create()
{
	int x;
//	struct tree *p;
	
	scanf("%d", &x);
	while (x != 0){
		insert(dat, x);
		scanf("%d", &x);
	}
}

int main(void)
{
	int i = 0;
//	struct tree *p;

	create();
	printf("display with first mode\n");
	display(head);
}
