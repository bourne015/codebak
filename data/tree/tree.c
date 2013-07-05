#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
	char data;
	struct tree *left;
	struct tree *right;	
} tree;

tree *insert(tree *p, char da)
{
	if (p == NULL) {
		p = (tree *)malloc(sizeof(tree));
		if (p == NULL) {
			printf("malloc error\n");
			return 0;
		} else {
			p->data = da;
			p->left = NULL;
			p->right = NULL;
			printf("%c--\n", p->data);
		}
		
	}
	else if (da < p->data) {
		printf("go left : ");
		p->left = insert(p->left, da);
	}
	else if (da >= p->data) {
		printf("go right : ");
		p->right = insert(p->right, da);
	}

	return p;
}

tree *create(tree *p)
{
	char data;
	int i = 0;
	tree *head;

	scanf(" %c", &data);
	while (data != '0') {
		p = insert(p, data);
		if (i++ == 0)
			head = p;
		scanf(" %c", &data);
	}

	return head;
}

void preorder(tree *p)
{
	if (p != NULL) {
		printf("%c--", p->data);
		preorder(p->left);
		preorder(p->right);
	}
}

void inorder(tree *p)
{
	if (p != NULL) {
		inorder(p->left);
		printf("%c--", p->data);
		inorder(p->right);
	}
}

void postorder(tree *p)
{
	if (p != NULL) {
		postorder(p->left);
		postorder(p->right);
		printf("%c--", p->data);
	}
}

int main(void)
{
	tree *p;

	p = create(p);
	printf("preorder : ");
	preorder(p);
	printf("\n");

	printf("inorder : ");
	inorder(p);
	printf("\n");

	printf("postorder : ");
	postorder(p);
	printf("\n");
}
