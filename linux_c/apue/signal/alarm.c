#include <stdio.h>
#include <signal.h>

void sig_alrm(int signo)
{
	printf("received\n");
	//signal(SIGALRM, SIG_DFL);
//	signal(SIGUSR1, SIG_DFL);
}

int main(void)
{
	if (signal(SIGUSR1, sig_alrm) == SIG_ERR)
		printf("error\n");

	while(1) {
		sleep(1);
		kill(getpid(), SIGUSR1);
	//	alarm(2);
	//	pause();
	}

	return 0;
}
