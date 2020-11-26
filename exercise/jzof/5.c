#include <stdio.h>
#include <stdlib.h>
#include "../leetcode/create.h"

void printrevert(struct ListNode *h)
{
    int *a, i = 0, k;
    struct ListNode *t = h;

    while (t) {
        i++;
        t = t->next;
    }
    a = (int *)malloc(sizeof(int)*i);
    for (t = h, k = i-1; k >= 0 && t!= NULL; k--) {
        a[k] = t->val;
        t = t->next;
    }
    for (k = 0; k < i; k++)
        printf("%d ", a[k]);
    printf("\n");
    free(a);
}

void printrevert2(struct ListNode *h)
{
    if (h) {
        printrevert2(h->next);
        printf("%d\n", h->val);
    }
}
int main(void)
{
    int a[] = {1,3,5,7,9};
    struct ListNode *l;

    l = create_list(a, sizeof(a)/sizeof(int));
    print_list(l);
    printrevert(l);
    printrevert2(l);
}
