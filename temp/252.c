#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
void func(void *a);
int main()
{
	char message[]={"just for test!!!"};
	pthread_t ppid;
	int *pid;
	int i;
	pid=pthread_create(&ppid, NULL, *func, (void *)message);
	pthread_join(ppid, (void *)pid);
	for(i=0;i<=10;i++) {
		printf("main process\n");
		sleep(1);
	}
}

void func(void *a)
{
	int j;
	for(j=0;j<=10;j++) {
		printf("second process %s\n",a);
		sleep(1);
	}
}
