#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	int i;
	struct stat buf;
	char *p;
	
	for (i = 1; i < argc; i++) {
		printf("%s: ", argv[i]);
		if (lstat(argv[i], &buf) < 0) {
			printf("lstat error\n");
			continue;
		}
		
		if (S_ISREG(buf.st_mode))
			p = "regular";
		else if (S_ISDIR(buf.st_mode))
			p = "dir";
		else if (S_ISCHR(buf.st_mode))
			p = "char file";
		else if (S_ISBLK(buf.st_mode))
			p = "block file";
		else if (S_ISFIFO(buf.st_mode))
			p = "FIFO";
		else if (S_ISLNK(buf.st_mode))
			p = "link file";
		else if (S_ISSOCK(buf.st_mode))
			p = "socker";
		else 
			p = "unknow file";
		printf("%s\n", p);
	}

	return 0;
}
