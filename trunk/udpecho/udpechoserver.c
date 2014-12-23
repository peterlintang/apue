/*
 * a very simple udp echo server
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERV_PORT	4567

int main(int argc, char **argv[])
{
	int	retval;
	int	sockfd;
	struct sockaddr_in serveraddr;
	struct sockaddr_in clientaddr;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		perror("socket");
		exit(1);
	} else {
		fprintf(stdout, "socket OK\n");
	}

	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERV_PORT);

	retval = bind(sockfd,(struct sockaddr *) &serveraddr, sizeof(serveraddr));
	if (retval == -1) {
		perror("bind");
		exit(2);
	}

	dg_echo(sockfd, (struct sockaddr *)&clientaddr, sizeof(clientaddr));

	return 0;
}
