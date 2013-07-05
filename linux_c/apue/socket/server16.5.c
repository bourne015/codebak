#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

#define QLEN 10
#define HOST_NAME_MAX 256
#define BUFLEN 128

int initserver(int type, const struct sockaddr *addr,
		socklen_t alen, int qlen)
{
	int fd;
	int err = 0;
	if ((fd = socket(addr->sa_family, type, 0)) < 0)
		return -1;
	if (bind(fd, addr, alen) < 0) {
		err = errno;
		goto errout;
	}
	if (type == SOCK_STREAM || type == SOCK_SEQPACKET) {
		if (listen(fd, qlen) < 0) {
			err = errno;
			goto errout;
		}
	}
	return (fd);

errout:
	close(fd);
	errno = err;
	return (-1);
}

int serve(int sockfd)
{
	int clfd;
	FILE *fp;
	char buf[BUFLEN];
	
	for (;;) {
		clfd = accept(sockfd, NULL, NULL);
		if (clfd < 0) {
			exit(1);
		}
		if ((fp = popen("usr/bin/uptime", "r")) == NULL) {
			send(clfd, buf, strlen(buf), 0);
		} else {
			while (fgets(buf, BUFLEN, fp) != NULL)
				send(clfd, buf, strlen(buf), 0);
			pclose(fp);
		}
		close(clfd);
	}
}

int main(int argc, char *argv[])
{
	struct addrinfo *ailist, *aip;
	struct addrinfo hint;
	int sockfd, err, n;
	char *host;

	if (argc != 1) {
		printf("input arg\n");
		return -1;
	}
	n = HOST_NAME_MAX;
	host = malloc(n);
	if (host == NULL) {
		printf("malloc error\n");
		return -1;
	}
	if (gethostname(host, n) < 0) {
		printf("gethost name error\n");
		return -1;
	}

//	daemonize("ruptimed");
	hint.ai_flags = AI_CANONNAME;
	hint.ai_family = 0;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = 0;
	hint.ai_addrlen = 0;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;

	if (err = getaddrinfo(host, "ruptime", &hint, &ailist))
		exit(-1);
	for (aip = ailist; aip != NULL; aip = aip->ai_next) {
		if ((sockfd = initserver(SOCK_STREAM, aip->ai_addr,
			aip->ai_addrlen, QLEN)) >= 0) {
			serve(sockfd);
			return 0;
		}
	}
	exit(1);
}
