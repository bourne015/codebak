#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

#define MYDIR "/home/fantao/myCODES/linux_c"

void printdir(char *dir, int depth)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	
	if ((dp = opendir(dir)) == NULL) {
		printf("can't open %s\n", dir);
		return;
	}

	chdir(dir);
	while ((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name, &statbuf);
		if (S_ISDIR(statbuf.st_mode)) {
			if (strcmp(".", entry->d_name) == 0 ||
				strcmp("..", entry->d_name) == 0)
				continue;

			printf("%*s%s/\n", depth, " ", entry->d_name);
			printdir(entry->d_name, depth+4);
		} else {
			printf("%*s%s/\n", depth, " ", entry->d_name);
		}
	}
	chdir("..");
	closedir(dp);
}

int main(void)
{
	printf("MYDIR:\n");

	printdir(MYDIR, 0);
	
	printf("done\n");
	return 0;
}
