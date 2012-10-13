#include "14.h"

int mycreate(void)
{
	FILE *fd;
	int create[all];
	int i;
	memset(create, '\0', all);
	fd = fopen("in.dat", "w");
	if (fd == NULL) return -1;
	for (i = 0; i < all; i++) {
		create[i] = rand()%8999+1000;
		fwrite(&create[i], sizeof(int), 1, fd);
		//printf("%d\t",create[i]);
	}
	fclose(fd);
	return 1;
}
