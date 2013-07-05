#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int fd1, fd2, fd3;
	char buf[] = "hello";
	char buf2[] = "next";
	char buf3[] = "third\n";
	if ((fd1 = open("file", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR)) < 0) {
		printf("open err\n");
		return 0;
	}
	write(fd1, buf, sizeof(buf));
	
	fd2 = dup(fd1);
	write(fd2, buf2, sizeof(buf2));
	
	fd3 = dup2(fd1, 7);
	write(fd3, buf3, fd3);
	return 0;
}
