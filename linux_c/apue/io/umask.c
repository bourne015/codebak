#include <stdio.h>
#include <fcntl.h>
#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
int main(void)
{
	umask(0);
	creat("1111", RWRWRW);

	umask(S_IRGRP | S_IWGRP);
	creat("2222", RWRWRW);
	
	return 0;
}
