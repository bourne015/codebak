#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<stdio.h>
#define size 50
int main()
{
	int fd;
	const char buffer[size]={"I'll write something!"};
	if(mkfifo("/home/fantao/c/fifo1", 0777)) {
		printf("creat error\n");
		exit(1);
	}
	fd=open("/home/fantao/c/fifo1", O_WRONLY);// | O_NONBLOCK);
	if(write(fd, buffer, size)!=-1) 
		printf("write success\n");
	close(fd);
}
