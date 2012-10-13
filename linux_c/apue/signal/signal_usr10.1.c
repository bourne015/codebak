#include <stdio.h>
#include <signal.h>

void sig_usr(int signo)
{
	if (signo == SIGUSR1)
		printf("received SIGUSR1\n");

	else if (signo == SIGUSR2)
		printf("received SIGUSR2\n");
	else
		printf("unknow signal\n");
}

int main(void)
{
        if (signal(SIGUSR1, sig_usr) == SIG_ERR)
                printf("sigusr1 error\n");

	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
		printf("sigusr2 error\n");

//	for (;;)
		pause();
}
