#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;
pthread_mutex_t mutex;

void thread_function(int *arg)
{
	int i;
	for (i = 0; i < 2; i++) {
	//	sleep(1);
		printf("thread :%d\n", arg);
		pthread_mutex_lock(&mutex);	
		//sem_wait(&sem);
	}
	pthread_exit("chile thread done");
}

int main()
{
	int m[3] ={2,3,4};
	pthread_t p[3];
	char *result;
	int res[4], i;
	//res[0] = sem_init(&sem, 0, 0);
	res[0] = pthread_mutex_init(&mutex, NULL);
	if (res[0] != 0) {
		printf("failed to init sem\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < 3; i++) {
		res[i] = pthread_create(&p[i], NULL, &thread_function, m[i]);
		if (res[i] != 0) {
			printf("create thread failed\n");
			exit(EXIT_FAILURE);	
		}
	}
	for (i = 0; i < 2; i++) {
	//	sem_post(&sem);
		printf("1\n");
	}
	for (i = 0; i < 6; i++) {
		sleep(1);
		//sem_post(&sem);
		pthread_mutex_unlock(&mutex);
	}
	for (i = 0; i < 3; i++)
		pthread_join(p[i], &result);
	printf("main:%s\n", result);
	pthread_mutex_destroy(&mutex);
	//sem_destroy(&sem);
	return 1;
}
