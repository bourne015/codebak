#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
int main()
{
	int pid;
	pid=fork();
	if(pid==0) {
		printf("I'm child process %d\n",getpid());
	}
	else if(pid==-1) {
		printf("error");
		exit(1);
	}
	else
	{
		printf("I'm parent process %d\n",getpid());
	}
}
