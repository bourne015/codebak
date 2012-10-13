#include <stdio.h>
#include <signal.h>

void func(int signo)
{
	printf("got it\n");
}

int main(void)
{
	struct sigaction act, oact;
	
	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	sigaction(SIGINT, &act, 0);
	pause();
}
