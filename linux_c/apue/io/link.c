#include <stdio.h>
#include <unistd.h>

int main(void)
{
	if (unlink("linkdir") < 0)
		printf("link error\n");

	return 0;
}
