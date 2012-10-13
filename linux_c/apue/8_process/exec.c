#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	int pid;
	if ((pid = fork()) == -1) {
		printf("fork error\n");
		return -1;
	} else if (pid == 0){
		printf("chile 1 process\n");
		execl("/bin/echo", "echo", "PATH", (char *)0);
		printf("chile 1 exit\n\n");
	}
	
	if (waitpid(pid, NULL, 0) < 0) {
		printf("wait error\n");
	//	exit(-1);
		return -1;
	}

	if ((pid = fork()) == -1) {
		printf("fork error\n");
	//	exit(-1)	;
		return -1;
	} else if (pid == 0) {
		printf("chile 2 process\n");
	//	execlp("echo", "echo", "chile 2", (char *)0);
		printf("chile 2 exit\n");
	}

	return 0;
		
}
