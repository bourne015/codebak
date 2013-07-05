#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <stdio.h>

#define BUFLEN 128
#define MAXSLEEP 128

int
connect_retry(int socketfd, const struct sockaddr *addr, socklen_t alen)
{
	int nsec;
	
	for (nsec = 1; nsec <= MAXSLEEP; nsec << 1) {
		if (connect(socketfd, addr, alen) == 0) {
			return 0;
		}

		if (nsec < MAXSLEEP/2)
			sleep(nsec);
	}

	return (-1);
}
void print_uptime(int socketfd)
{
	int n;
	char buf[BUFLEN];
	
	while ((n = recv(socketfd, buf, BUFLEN, 0)) > 0)
		write(STDOUT_FILENO, buf, n);

	if (n < 0)
		printf("recv error\n");
}

int main(int argc, char *argv[])
{
	struct addrinfo *ailist, *aip;
	struct addrinfo hint;
	int socketfd, err;

	if (argc != 2) {
		printf("intput 2 arg\n");
		return 0;
	}

	hint.ai_flags = 0;
	hint.ai_family = 0;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = 0;
	hint.ai_addrlen = 0;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;
	if ((err = getaddrinfo(argv[1], "ruptime", &hint, &ailist)) != 0) {
		printf("getaddrinfo error\n");
		return -1;
	}

	for (aip = ailist; aip != NULL; aip = aip->ai_next) {
		if ((socketfd = socket(aip->ai_family, SOCK_STREAM, 0)) < 0)
			err = errno;
		if (connect_retry(socketfd, aip->ai_addr, aip->ai_addrlen) < 0) {
			err = errno ;
		} else {
			print_uptime(socketfd);
			exit(0);
		}
	}
	fprintf(stderr, "can't, connetc, to %s\n", argv[1]);
	exit(1);

}
