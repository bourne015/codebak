/*
 *swap list
 * */
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
} listnode;

listnode *createlist(void)
{
    listnode *head, *p, *tmp;
    int i = 0;

    tmp = malloc(sizeof(listnode));
    head = tmp;
    for (i = 1; i <= 10; i++) {
        tmp->val = i;
        p = tmp;
        tmp = malloc(sizeof(listnode));
        p->next = tmp;
    }
    
    p->next = NULL;

    return head;
}

listnode *myswaplist(listnode *head)
{
    listnode *p1, *p2, *p3;
    
    p1 = head;
    p2 = p1->next;
    p3 = p2->next;
    p1->next = NULL;
    while (p2->next != NULL) {
        p2->next = p1;
        p1 = p2;
        p2 = p3;
        p3 = p3->next;

    }
    p2->next = p1;

    return p2;
}

int main(void)
{
    int n;
    listnode *head, *p;
    head = createlist();
    p = head;

    while (head != NULL) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
    head = p;
    head = myswaplist(head);
    while (head != NULL) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}
