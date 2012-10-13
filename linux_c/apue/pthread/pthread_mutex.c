#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

#define WORK_SIZE 1024

char work_area[WORK_SIZE];
int time_to_exit = 0;
pthread_mutex_t work_mutex;


void *thread_function(void *arg)
{
	sleep(1);
	pthread_mutex_lock(&work_mutex);
	while (strncmp("end", work_area, 3) != 0) {
		printf("your input %d chars\n", strlen(work_area) - 1);
		work_area[0] = '\0';
		pthread_mutex_unlock(&work_mutex);
		sleep(1);
		pthread_mutex_lock(&work_mutex);
		while (work_area[0] == '\0') {
			pthread_mutex_unlock(&work_mutex);
			sleep(1);
			pthread_mutex_lock(&work_mutex);
		}
	}
	time_to_exit = 1;
	work_area[0] = '\0';
	pthread_mutex_unlock(&work_mutex);
	pthread_exit(0);
}

int main(void)
{
	int res;
	pthread_t a_thread;
	void *thread_result;

	res = pthread_mutex_init(&work_mutex, NULL);
	if (res != 0) {
		printf("init error\n");
		exit(EXIT_FAILURE);
	}

	res = pthread_create(&a_thread, NULL, thread_function, NULL);
	if (res != 0) {
		printf("create error\n");
		exit(EXIT_FAILURE);
	}

	pthread_mutex_lock(&work_mutex);
	while (!time_to_exit) {
		printf("input some text, 'end' to finish:\n");

		fgets(work_area, WORK_SIZE, stdin);
		pthread_mutex_unlock(&work_mutex);
		while (1) {
			pthread_mutex_lock(&work_mutex);
			if (work_area[0] != '\0') {
				pthread_mutex_unlock(&work_mutex);
				sleep(1);
			} else {
				break;
			}
		}		
	}

	pthread_mutex_unlock(&work_mutex);
	printf("\nwaiting for thread to finish...\n");
	res = pthread_join(a_thread, &thread_result);
	if (res != 0) {
		printf("pthread_join error\n");
		exit(EXIT_FAILURE);
	}

	printf("thread joined\n");
	pthread_mutex_destroy(&work_mutex);
	exit(EXIT_SUCCESS);
}
