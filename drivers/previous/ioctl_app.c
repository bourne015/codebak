#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

#include"char_def.h"

int main(void)
{
	int fd;
	int cmd;
	int arg;
	fd = open("/dev/memdev", O_RDWR);
	if (fd == -1) {
		printf("can't open device!\n");
		return -1;
	}
	
	cmd = MEM_IOCSTART;
	if (ioctl(fd, cmd, &arg) < 0) {
		printf("call cmd memdev failed!\n");
		return -1;
	}

	cmd = MEM_IOCSEND;
	arg = 12345;
	if (ioctl(fd, cmd, &arg) < 0) {
		printf("call mem_iocsend failed!\n");
		return -1;
	}
	
	cmd = MEM_IOCGET;
	if (ioctl(fd, cmd, &arg) < 0) {
		printf("call mem_iocget failed!\n");
		return -1;
	}
	printf("get a data from kernel:%d\n",arg);
	
	close(fd);
	return 0;
}
