#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>
#include<stdio.h>
#define size 50
int main()
{
	int fd,fork_fd;
	const char buf[size],buffer[size]={"it's amazing!"};
	if(mkfifo("/home/fantao/c/my_fifo", 0777)!=0) {
		printf("creat error\n");
		exit(1);
	}
	fork_fd=fork();
	if(fork_fd==-1) {
		printf("fifo error\n");
		exit(1);
	}
	else if(fork_fd==0) {
		fd=open("/home/fantao/c/my_fifo", O_WRONLY);
		write(fd, buffer, size);
		close(fd);
	}
	else
	{
		fd=open("/home/fantao/c/my_fifo", O_RDONLY);
		read(fd, buf, size);
		printf("what I read: %s\n",buf);
	}
}
