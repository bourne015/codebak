#include <stdio.h>
#include <string.h>

#define size 4096

int main()
{
	FILE *fd;
	char buf[] = "just for test";
	char buf2[size];

	memset(buf2, '\0', size);

	fd = fopen("/dev/tao", "w+");
	if (fd == NULL) {
		printf("can't open device\n");
		return -1;
	}
	

	fwrite(buf, sizeof buf, 1, fd);
	
	fread(buf2, sizeof(buf), 1, fd);

	printf("what I read: %s\n", buf2);
	
	fclose(fd);
	return 0;
	
}
