#include "stu_head.h"

STU *delete_stu(STU *head)
{
	int del_max = 10;
	int i = 0;
	int del_num[del_max];

	STU *p1, *p2 = head;
	printf("the stu's number to del(max is 10, end with 0):");

//	while (getchar() == '\n');	//to ignore the '\n' ??
					//use this then scanf-a[0] can't work

	do {
		scanf("%d", &del_num[i]);
		printf("del_num[%d] = %d\n", i, del_num[i]);
	} while (del_num[i++] != 0 && i < del_max);

	i = 0;
	while (del_num[i] != 0) {
		printf("deleting\n");
		p1 = head;
		if (p1->num == del_num[i]) {
			head = p1->next;
			i++;
			continue;
		} else {
			while(p1->next->num != del_num[i]) {
				if (p1->next->next == NULL) { 
					printf("can't find stu num %c\n",
						del_num[i]);
					break;
				}
				p1 = p1->next;
			}
		
			p1->next = p1->next->next;
		}
		i++;
	}
	printf("done\n");
	return head;
}

