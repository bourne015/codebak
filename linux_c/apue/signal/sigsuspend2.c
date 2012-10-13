#include <stdio.h>
#include <signal.h>

volatile sig_atomic_t quitflag;// = 1;

void sig_int(int signo)
{
	if (signo == SIGINT)
		printf("\nreceived SIGINT\n");
	else if (signo == SIGQUIT) {
		printf("\nreceived SIGQUIT\n");
		quitflag = 1;
	}
}

int main(void)
{
	sigset_t newmask, oldmask, zeromask;

	if (signal(SIGINT, sig_int))
		goto failed;
	if (signal(SIGQUIT, sig_int))
		goto failed;

	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);

	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		goto failed;
	
	printf("now we start func\n");
	while (quitflag == 0)
		sigsuspend(NULL);
		//pause();
	quitflag = 0;

	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		goto failed;

	return 0;

	failed:
		printf("errot\n");
		return -1;
}
