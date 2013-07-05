#include "stu_head.h"

STU *display(void)
{
        FILE *fd;
        int n = 0;
        STU *head, *res, *temp;

        fd = fopen("STU_DATA", "r");
        if (fd == NULL) {
                printf("can't open data\n");
                exit(0);
        }

        head = malloc(sizeof(STU));
        while (fscanf(fd, "%d %s %d", &head->num, head->name,
                        &head->score) != EOF) {
                printf("%d %s %d\n", head->num, head->name, head->score);

                if (n++ == 0) res = head;
                temp = head;
                head = malloc(sizeof(STU));
                temp->next = head;
        }
        fclose(fd);
        temp->next = NULL;
        free(head);
        return res;
}

void preview(STU *head)
{
        int n = 0;
        while (head != NULL) {
                printf("%d %s %d\n", head->num, head->name, head->score);
                head = head->next;
        }

}

