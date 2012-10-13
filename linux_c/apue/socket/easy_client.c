#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	int sockfd, len;
	struct sockaddr_un address;
	int res;
	char ch = 'F';

	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

	address.sun_family = AF_UNIX;
	//address.sin_addr.s_addr = inet_addr("127.0.0.1");
	//address.sin_port = 9734;
	strcpy(address.sun_path, "server_socket");
	len = sizeof(address);

	res = connect(sockfd, (struct sockaddr *)&address, len);
	
	if (res == -1) {
		printf("error\n");
		return -1;
	}

	write(sockfd, &ch, 1);
	read(sockfd, &ch, 1);
	printf("char from server = %c\n", ch);
	close(sockfd);
	return 0;
}
