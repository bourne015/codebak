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

int menu(void)
{
	int choice, c;

	printf("\n\t-------------------------------\n");
	printf("\t\t1: create a tree\n\n");
	printf("\t\t2: insert a child\n\n");
	printf("\t\t3: display with preorder\n\n");
	printf("\t\t4: display with inorder\n\n");
	printf("\t\t5: display with postorder\n\n");
	printf("\t\t6: quit\n\n");
	printf("\t-------------------------------\n");

//	scanf(" %c", &choice);
	if ((c = getchar()) == '\n')
		choice = getchar();
	else
		choice = c;

	return choice;
}

int main(void)
{
	tree *p;
	int choice;
	char da;

	while (1) {
		choice = menu();
		printf("your choice: %c\n", choice);
		switch (choice) {
			case '1':
				printf("now input the data: ");
				p = create(p);
				printf("test:%c\n", p->data);
				break;
			case '2':
				printf("input the data to insert:");
				scanf(" %c", &da);
				insert(p, da);
				break;
			case '3':
				printf("preorder : ");
				preorder(p);
				printf("\n");
				break;
			case '4':
				printf("inorder : ");
				inorder(p);
				printf("\n");
				break;
			case '5':	
				printf("postorder : ");
				postorder(p);
				printf("\n");
				break;
			case '6':
				return;
			default:	
				printf("wrong choice!\n");
				break;
		}				
	}

}
