#include<unistd.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#include<stdio.h>
#define size 50
int main()
{
	int fork_fd,shm_fd;
	const char *shm_addr,buffer;
	key_t key;
	fork_fd=fork();
	if(fork_fd==-1) {
		printf("fork error\n");
		exit(1);
	}
	else if(fork_fd==0) {
		printf("I'm child process...\n");
		key=ftok("/home/fantao/c/in.txt", 1);
		shm_fd=shmget(key, size, IPC_CREAT | 0666);
		if(shm_fd==-1) {
			printf("shmget error\n");
			exit(EXIT_FAILURE);
		}
		shm_addr=shmat(shm_fd, (void *)0, 0);
		if(shm_addr==-1) {
			printf("shmat error\n");
			exit(EXIT_FAILURE);
		}
//		shm_addr="good!";
		printf("successed to share memary\n");
	}
	else {
		wait(NULL);
		printf("I'm parent process...\n");
		shm_fd=shmget(IPC_PRIVATE, size, 0666);
		shm_addr=shmat(shm_fd, (void *)0, 0);
	//	printf("%s\n",*shm_fd);
		switch(read(shm_addr, buffer, size))
		{
			case 0:printf("empty\n");break;
			case -1:printf("error\n");break;
			default:printf("%s\n",buffer);break;
		}	
	}
}
