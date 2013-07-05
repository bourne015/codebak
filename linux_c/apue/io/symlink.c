#include <stdio.h>
#include <unistd.h>

int main(void)
{
	if (symlink("../pthread", "symlink") < 0)
		printf("error\n");

	return 0;
}
