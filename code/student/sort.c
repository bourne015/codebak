#include "stu_head.h"

STU *sort_stu(STU *head)
{
        STU *p1, *p2, *p;
        int i = 0;

        p1 = (STU *)malloc(sizeof(STU));
        p1->next = head;
        head = p1;

//	for (p = head; p->next->next != NULL; p = p->next) {
        for (i = 0; i < 3; i++) {
		printf("for1\n");
                for (p1 = head; p1->next->next != NULL; p1 = p1->next) {
			printf("for2--");
                        if (p1->next->num > p1->next->next->num) {
				printf("if\n");
				p2 = p1->next;
				p1->next = p2->next;
				p2->next = p2->next->next;
				p1->next->next = p2;
                        }
                }
        }

        p1 = head;
        head = head->next;
        free(p1);
        return  head;
}
