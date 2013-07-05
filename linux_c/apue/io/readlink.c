#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char buf[4096];

	if (readlink("symlink", buf, 4096) < 0)
		printf("error\n");
		
	printf("%s\n", buf);

	return 0;
}
