#include <stdio.h>
#include <unistd.h>

int glob = 1;

int main(void)
{
	int var = 10;
	pid_t pid;

	printf("before vfork\n");
	if ((pid = vfork()) < 0) {
		printf("vfork error\n");
		return -1;
	} else if (pid == 0) {
		glob++;
		var++;
		_exit(0);
	}

	printf("pid = %d, glob = %d, var = %d\n",
		getpid(), glob, var);
}
