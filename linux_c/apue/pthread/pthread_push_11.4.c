#include <stdio.h>
#include <string.h>
#include <pthread.h>

void clean(void *arg)
{

	printf("clean: %s\n", (char *)arg);

}

void *func1(void *arg)
{
	printf("thread 1 start\n");

	pthread_cleanup_push(clean, "thread 1 firsh handler");
	pthread_cleanup_push(clean, "thread 1 second handler");

	printf("thread 1 push completed\n");

	if (arg)
		return ((void *)1);

	prhread_cleanup_pop(0);
	pthread_cleanup_pop(0);

	return ((void *)1);
}

void *func2(void *arg)
{
	printf("thread 2 start\n");
	pthread_cleanup_push(clean, "thread 2 first handler");
	pthread_cleanup_push(clean, "thread 2 second handler");
	printf("thread 2 push completed\n");

	if (arg)
		pthread_exit((void *)2);

	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);

	pthread_exit((void *)2);
}

int main(void)
{
	pthread_t thread1, thread2;
	void *pth_ret;
	int ret;

	ret = pthread_create(&thread1, NULL, func1, (void *)1);
	if (ret != 0)
		goto failed;

	ret = pthread_create(&thread2, NULL, func2, (void *)1);
	if (ret != 0)
		goto failed;
	ret = pthread_join(thread1, &pth_ret);
	if (ret != 0)
		goto failed;
	printf("thread 1 exit with code %d\n",  pth_ret);
	
	ret = pthread_join(thread2, &pth_ret);
	if (ret != 0)
		goto failed;
	printf("thread 2 exit with code %d\n", pth_ret);

	exit(0);

	failed:
		printf("thread error\n");
		return 1;

}
