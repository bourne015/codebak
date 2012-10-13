#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include"led_def.h"
int main(int argc, char *argv[])
{
	int fd;
	int ioarg =1, cmd;
	char arg;
	if (argc !=2) {
		printf("please input a valid\n");
		return -1;
	}
	fd = open("/dev/ledname", O_RDWR);
	if (fd == -1) {
		printf("can't open device\n");
		return -1;
	}
	cmd = MEM_IOCSTAT;
	ioctl(fd, cmd, ioarg);
	printf("the led stat is %d\n",ioarg);	
	
	printf("your input2: %c\n",*argv[1]);
	//sleep(1);
	arg = *argv[1];
	printf("arg=%c\n",arg);
	cmd = MEM_IOCSET;
	ioctl(fd, cmd, &arg);
	close(fd);
	return 0;
}
