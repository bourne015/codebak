#include <stdio.h>
#include <stdlib.h>

struct list
{
	int val;
	struct list *next;
};

struct list *createlist()
{
    int i;
    struct list *l,*p, *t;

    l = malloc(sizeof(struct list));
    p = l;
    for (i = 1; i < 10; i++) {
        t = malloc(sizeof(struct list));
        t->val = i;
        p->next = t;
        p = t;
    }
    return l->next;
}

struct list *revertlist(struct list *l)
{
	struct list *p, *t;

	p = l->next;
	t = p->next;
    l->next = NULL;
	while (p != NULL) {
		p->next = l;
		l = p;
		p = t;
        if (t!=NULL)
		    t = t->next;
	}
	return l;
}

int main(void)
{
	struct list *l, *t;

	l = createlist();
	t = revertlist(l);

    while (t != NULL) {
        printf("%d\n", t->val);
        t = t->next;
    }
}
