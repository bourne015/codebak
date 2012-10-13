#include "stu_head.h"

void find_stu(STU *head)
{
        int find_num;
        printf("\nthe student number is?\n");
        scanf("%d", &find_num);
        while (head->num != find_num) {
                if (head->next == NULL) {
                        printf("there aren't this student\n");
                        return;
                }
                head = head->next;
        }       
        
        printf("this student info is:\n");
        printf("%d %s %d\n", head->num, head->name, head->score);
}
