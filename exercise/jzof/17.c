/*
 * merge two list in order
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    int val;
    struct list *next;
} listnode;

listnode *createlist(int d[])
{
    listnode *head, *p, *tmp;
    int i = 0;

    tmp = malloc(sizeof(listnode));
    head = tmp;
    for (i = 0; i < 4; i++) {
        tmp->val = d[i];
        p = tmp;
        tmp = malloc(sizeof(listnode));
        p->next = tmp;
    }

    p->next = NULL;

    return head;
}

listnode *mergelist(listnode *l1, listnode *l2)
{
	listnode *head, *tl,*th;

	if (l1->val < l2->val) {
		head = l1;
        l1 = l1->next;
    } else {
		head = l2;
        l2 = l2->next;
    }
    th = head;
	while (l1 != NULL && l2 != NULL) {
		if (l1->val < l2->val) {
            head->next = l1;
            l1 = l1->next;
		} else {
            head->next = l2;
            l2 = l2->next;
		}
        head = head->next;
	}
	if (l1 == NULL)
		head->next = l2;
	else
		head->next = l1;
    return th;
}

int main(void)
{
	int a[] = {1,30,50,70}, b[] = {2,4,6,80};
	struct list *l, *l1, *l2;

	l1 = createlist(a);
	l2 = createlist(b);

	l = mergelist(l1, l2);

	while (l != NULL) {
		printf("%d\n", l->val);
		l = l->next;
	}
}
