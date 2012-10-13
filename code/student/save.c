#include "stu_head.h"

int save(STU *head)
{
	FILE *fd;

	fd = fopen("STU_DATA", "w+");
	if (fd == NULL) {
		printf("can't create data\n");
		return 0;
	}

	while (head != NULL) {
		fprintf(fd, "%d %s %d\n", head->num, head->name,
			head->score);
		head = head->next;
	}

	fclose(fd);
	return 1;
}

