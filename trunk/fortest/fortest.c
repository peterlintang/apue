

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
//#include <readline/readline.h>
//#include <readline/history.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
	int	sockfd;
	struct sockaddr_in seraddr;
	char read_stdin[4097];
	char readbuf[4097];

	bzero(&seraddr, sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port   = 3456;
	inet_pton(AF_INET, "127.0.0.1", &seraddr.sin_addr);
//	inet_pton(AF_INET, "192.168.253.119", &seraddr.sin_addr);
//	memcpy(&seraddr.sin_addr, "192.168.253.119", sizeof(struct in_addr));

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("socket");
		exit(1);
	}

	if (connect(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)) == 0) {
		fprintf(stdout, "connect to server success!\n");
	} else {
		perror("connect");
		exit(2);
	}

	while (gets(read_stdin) != NULL)
	{
		write(sockfd, read_stdin, strlen(read_stdin));
		read(sockfd, readbuf, 4096);
		puts(readbuf);
	}

	close(sockfd);
	return 0;
}
