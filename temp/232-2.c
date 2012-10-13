#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<stdio.h>
#define sizes 50
int main()
{
	int fd;
	const char buf[sizes];
	fd=open("/home/fantao/c/fifo1", O_RDONLY);// | O_NONBLOCK);
	if(read(fd, buf, sizes)==-1) {
		printf("read error\n");
		exit(1);
	}
	else 
	{
		printf("what I read is: %s\n",buf);
		close(fd);
	}
	
}
