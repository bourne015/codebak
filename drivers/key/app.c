#include <stdio.h>

int main()
{
	FILE *fd;
	unsigned char key_val;

	fd = fopen("/dev/key", "r");
	if (fd == NULL) {
		printf("open err\n");
		return -1;
	}
	
	printf("open done\n\n\n");

	while (1) {
		printf("now reading \n\n");
		fread(&key_val, 1, 1, fd);
		printf("%c\n", key_val);
	}

	fclose(fd);
}
