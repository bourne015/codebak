#include <stdio.h>
#include <unistd.h>

int func(void)
{
	pid_t pid;
	if ((pid = vfork()) < 0) {
		printf("vfork error\n");
		return 0;
	} 
/*	else if (pid == 0) {
		printf("this is chile\n");
		_exit(0);
	}

	printf("this is parent\n");
	return 0;
*/
}

int main(void)
{
	printf("this is main\n");

	func();
	printf("done\n");
	_exit(0);
}
