#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void)
{
	int ser_fd, len, cli_len, cli_fd;
	struct sockaddr_in ser_addr, cli_addr;
	
	ser_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	ser_addr.sin_family = AF_UNIX;
	len = sizeof(ser_addr);
	bind(ser_fd, (struct sockaddr *)&ser_addr, len);
	listen(ser_fd, 5);
	while (1) {
		char ch;
		printf("server waiting\n");
		
		cli_len = sizeof(cli_addr);
		cli_fd = accept(ser_fd, (struct sockaddr *)*cli_addr,&cli_len);
		
		read(cli_fd, &ch, 1);
		ch++;
		write(cli_fd, &ch, 1);
		close(cli_fd);
}
