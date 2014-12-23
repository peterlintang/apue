
/*
 * my simple echo client. it write what the stdin to the 
 * server, and then read from the server, echo the result
 * to stdout
 */

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
	int 	i;
	int 	readcount;
	int	sockfd;
	struct sockaddr_in seraddr;
	char read_stdin[4097];
	char readbuf[4097];

	bzero(&seraddr, sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port   = 3456;
//	inet_pton(AF_INET, "127.0.0.1", &seraddr.sin_addr);
	inet_pton(AF_INET, "192.168.253.103", &seraddr.sin_addr);
//	memcpy(&seraddr.sin_addr, "192.168.253.119", sizeof(struct in_addr));

	/* for test how to deal with mutilple signal */
	/* it seems that the OS has queueed the signals */
	for (i = 0; i < 1; i++) {
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
	}

/* original
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
*/
	while (gets(read_stdin) != NULL)
	{
		write(sockfd, read_stdin, strlen(read_stdin));
		readcount = read(sockfd, readbuf, 4096);
		if (readcount > 0) readbuf[readcount]='\0';
		puts(readbuf);
	}

	close(sockfd);
	return 0;
}
