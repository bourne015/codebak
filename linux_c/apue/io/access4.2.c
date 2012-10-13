#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
		return 0;
	if (access(argv[1], R_OK) < 0)
		printf("can't read\n");
	else
		printf("read ok\n");

	if (access(argv[1], W_OK) < 0)
		printf("can't write\n");
	else
		printf("write ok\n");
	return 0;
}
