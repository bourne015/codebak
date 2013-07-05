#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
	
	int data;
	int hight;
	struct tree *left;
	struct tree *right;
} tree;


struct tree *insert(tree *p, int c)
{
	if (p == NULL) {
		p = malloc(sizeof(tree));
		if (p == NULL) {
			printf("mem error\n");
			return 0;
		}
		p->data = c;
		p->left = NULL;
		p->right = NULL;
		
	} else {
		if (c > p->data) {
			printf("go right--\n");
			p->right = insert(p->right, c);
		}
		else if (c <= p->data) {
			printf("go left--\n");
			p->left = insert(p->left,  c);
		}	
	}
}

struct tree *create(tree *p)
{
	int c, count;
	tree *head;

	printf("input data:");
	scanf("%d", &c);

	while (c != 0) {
		p = insert(p, c);
		if (count++ == 0)
			head = p;	
		scanf("%d", &c);
	}

	return head;
}

void preorder(tree *p)
{
	if (p != NULL) {
		printf("%d--", p->data);
		preorder(p->left);
		preorder(p->right);
	}
}

int main(void)
{
	tree *p;

	p = create(p);

	printf("preorder\n");
	preorder(p);
}
