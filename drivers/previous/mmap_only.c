#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <sys/mman.h>
#include<string.h>
//#include<memory.h>
#include<stdlib.h>
#include"char_def.h"

int main()
{
	int fd;
	char *start;
	char *buff;
	fd = open("/dev/memdev", O_RDWR);
	if(fd ==-1) {
		printf("error,can't open device!\n");
		return -1;
	}
	buff = malloc(100);
	memset(buff, 0, 100);
	start = mmap(NULL, 100, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	
	strcpy(buff, start);
	sleep(1);
	printf("buff 1 (it's empty at first):%s\n",buff);
	
	strcpy(start, "just for test!");
	memset(buff, 0, 100);
	strcpy(buff, start);
	sleep(1);
	printf("buff 2 :%s\n",buff);
	
	munmap(start, 100);
	free(buff);
	close(fd);
	return 0;
}
