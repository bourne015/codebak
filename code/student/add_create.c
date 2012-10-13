#include "stu_head.h"

STU *mycreate(void)
{
	int n = 0;
	STU *p1, *p2, *head;

	p1 = malloc(sizeof(STU));
	scanf("%d", &p1->num);
	while (p1->num != 0) {
		n++;
		scanf("%s%d", p1->name, &p1->score);
		if (n == 1) head = p1;
		p2 = p1;

		p1 = malloc(sizeof(STU));
		scanf("%d", &p1->num);
		p2->next = p1;
	}
	p2->next = NULL;
	free(p1);
	return head;
}

STU *add_stu(STU *head)
{
	STU *p1;
	int count, i;
	int more;
	do {
		printf("how many student do you want to add:");
		scanf("%d", &count);
		for (i = 0; i < count; i++) {
			p1 = malloc(sizeof(STU));
			scanf("%d%s%d", &p1->num, p1->name, &p1->score);
			if (head == NULL) {
				head = p1;
				head->next = NULL;
			} else {
				p1->next = head;
				head = p1;
			}
		}
		printf("do you wand to add more?y/n");
		while (getchar() == '\n'); //just to ignore the '\n'
		more = getchar();
	} while(more == 'y' && more == 'Y');
		
	return head;
}
