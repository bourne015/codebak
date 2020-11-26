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

int main(void)
{
	struct list *l, *t, *p;

	l = createlist();
	
}
