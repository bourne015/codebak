/*this app is to show the problem when use args*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
struct foo {
	int a, b, c, d;
};

void printfoo(const char *s, const struct foo *fp)
{
	printf("%s", s);
	printf("  structure  at 0x%x\n", (unsigned int)fp);
	printf("  foo.a = %d\n", fp->a);
	printf("  foo.b = %d\n", fp->b);
	printf("  foo.c = %d\n", fp->c);
	printf("  foo.d = %d\n", fp->d);
}

void *func1(void *arg)
{
	struct foo *foo = malloc(sizeof(struct foo)); //add this, then is can be work

	*foo = (struct foo){1, 2, 3, 4};
	
	printfoo("thread 1:\n", foo);
	pthread_exit(foo);
}

void *func2(void *arg)
{
	printf("thread 2: ID is %d\n", (unsigned int)pthread_self());
	pthread_exit((void *)0);
}

int main(void)
{
	int err;
	pthread_t tid1, tid2;
	struct foo *fp;

	err = pthread_create(&tid1, NULL, func1, NULL);
	if (err != 0) {
		printf("can't create thread\n");
		return err;
	}
	err = pthread_join(tid1, (void *)&fp);
	if (err != 0) {
		printf("can't create thread\n");
		return err;
	}
	sleep(1);
	printf("starting second thread\n");

	err = pthread_create(&tid2, NULL, func2, NULL);
	if (err != 0) {
		printf("can't create thread2\n");
		return err;
	}

	sleep(1);
	printfoo("parent:\n", fp);
	free(fp);
	return 0;
}
