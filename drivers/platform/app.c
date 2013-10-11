#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int fd;
	int val = 1;

	fd = open("/dev/mykey", O_RDWR);
	if (fd < 0) {
		printf("open err\n");
		return -1;
	}

	if (argc != 2) {
		printf("Usage : \n");
		return -1;
	}
	
	if (strcmp(argv[1], "on") == 0) {
		val = 1;
	} else {
		val = 0;
	}
	write(fd, &val, 4);

	return 0;
}
