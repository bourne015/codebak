#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#define size 50
int main()
{
	int pipe_fd[2],fork_fd;
	const char buffer[size];//={"hello world!"};
	if(pipe(pipe_fd)!=0) {
		printf("pipe error\n");
		exit(0);
	}
	fork_fd=fork();
	if(fork_fd==0) {
		sleep(1);
		read(pipe_fd[0], buffer, size);
		printf("the message in pipe is %s\n",buffer);
		exit(0);
	}
	else if(fork_fd==-1) {
		printf("fork error\n");
		exit(1);
	}
	else
	{
		write(pipe_fd[1], "it's ok !!!", size);
		printf("parent pid writed sth\n");
		sleep(2);
	}

}
