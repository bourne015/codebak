#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
int main()
{
	FILE *fd;
	char buff[4096];
	strcpy(buff, "just for test!!");
	printf("%s\n",buff);
	fd = fopen("/dev/memdev","r+");//O_TRUNC,S_IRUSR|S_IWUSR);
	if(fd == NULL) {
		printf("erro,can't open device!\n");
		return -1;
	}
	fwrite(buff, sizeof(buff), 1, fd);
	printf("write worked\n");
	
	//fseek(fd, 0, SEEK_SET);
	//printf("llseek worked\n");
	
	strcpy(buff,"buff is null now!");
	printf("%s\n",buff);
	fread(buff, sizeof(buff), 1, fd);
	printf("read worked\n buff:%s\n",buff);
	return 0;
}
