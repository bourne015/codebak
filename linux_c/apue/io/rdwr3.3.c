#include <stdio.h>
#include <unistd.h>

#define BUFF 4096

int main(void)
{
	char buf[BUFF];
	int n;
	
	while ((n = read(STDIN_FILENO, buf, BUFF)) > 0)
		if (write(STDOUT_FILENO, buf, n) != n)
			exit(-1);
	if (n < 0)
		printf("error\n");
	exit(0);
}

