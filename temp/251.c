#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
void func(void *a);
void main()
{
	int i;
	char text[]={"just for test!"};
	pthread_t pid;
	pthread_create(&pid, NULL, *func, (void *)text);
	for(i=0;i<=10;i++) {
		printf("main process\n");
		sleep(1);
	}
}

void func(void *a)
{
	int j;
	for(j=0;j<=10;j++) {
		printf("sceond process %s\n",a);
		sleep(1);
	}
}
