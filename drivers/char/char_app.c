#include <stdio.h>
#include <string.h>
#define size 4096
int main()
{
	FILE *fd;
	char buf[size] = "just for test";
	char buf2[size];
	memset(buf2, '\0', size);
	fd = fopen("/dev/tao", "r+");
	if (fd ==NULL) {
		printf("can't open device\n");
		return -1;
	}
	printf("now test write\n");
	printf("buf to write:%s\n", buf);
	fwrite(buf, sizeof(buf), 1, fd);
	printf("write done\n");
	
	fseek(fd, 0, SEEK_SET);
	printf("lseek done\n");

	printf("then read\n");
	fread(buf2, sizeof(buf), 1, fd);
	printf("what I read:%s\n", buf2);
	
	return 0;
	
}
