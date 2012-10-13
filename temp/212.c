#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<stdio.h>
#define size 50
int main()
{
	int in_fd;
	FILE *out_fd;
	const char buffer[size],*filename="/home/fantao/c/out.txt";
	in_fd=open("/home/fantao/c/in.txt", O_RDWR);
	if(read(in_fd, buffer, size)==-1) {
		printf("read error\n");
		exit(1);
	}	
	out_fd=fopen(filename, "wb");//O_CREAT|O_RDWR ,S_IRUSR|S_IWUSR);
	if(fwrite(buffer, size, 1, out_fd)) {
		printf("done!\n");
	}
}
