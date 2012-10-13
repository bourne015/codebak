#include <stdio.h>
#include <signal.h>

void sig_int(int signo)
{
	printf("\nget a sigint\n");
}

int main(void)
{
	sigset_t newmask, waitmask, oldmask;

	printf("program start:\n");

	if (signal(SIGINT, sig_int) == SIG_ERR)
		goto failed;
	sigemptyset(&waitmask);
	sigaddset(&waitmask, SIGUSR1);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);

	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		goto failed;
	printf("in critical region: \n");

	if (sigsuspend(&waitmask) != -1)
		goto failed;
	printf("after sigsuspend: \n");

	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		goto failed;
	printf("program exit: \n");
	return 0;

	failed:
		printf("error\n");
		return -1;
}
