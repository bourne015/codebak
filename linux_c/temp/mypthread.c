#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

char message[] = "hello";
void *thread_function(void *arg)
{
	int i;
	for (i = 0; i < 10; i++)  
		printf("2:%s\n", arg);
	pthread_exit("chile thread done");
	//sleep(0.5);
}

int main()
{
	int res;
	void *result;
	int i;
	pthread_t p;
	res = pthread_create(&p, NULL, thread_function, message);
	if (res != 0) {
		printf("thread create failed\n");
		exit(EXIT_FAILURE);
	}
	
	for (i = 0; i < 10; i++)
		printf("1\n");
	pthread_join(p, &result);
	printf("main:%s\n", result);
	//sleep(1);
	return 1;
}

