#include <stdio.h>
#include <signal.h>

void sig_quit(int signo)
{
	printf("\ncatched SIGQUIT\n");
	if (signal(SIGQUIT, SIG_DFL) < 0)
		printf("failed to reset SIGQUIT\n");
}

int main(void)
{
	sigset_t newmask, oldmask, pendmask;

	if (signal(SIGQUIT, sig_quit) == SIG_ERR)
		goto failed;

	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);

	if (sigprocmask(SIG_UNBLOCK, &newmask, &oldmask) < 0)
		goto failed;

	sleep(5);
	if (sigpending(&pendmask) < 0)
		goto failed;

	if (sigismember(&pendmask, SIGQUIT))
		printf("\nSIGQUIT pending\n");
	
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		goto failed;
	printf("SIGQUIT unblocked\n");

	sleep(2);
	return 0;

	failed:	printf("error");
		return -1;
}
