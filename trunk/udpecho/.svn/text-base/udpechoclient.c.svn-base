/*
 * a very simple udp echo client program
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERV_PORT 4567

#define MSG_LEN		4096

int main(int argc, char **argv)
{
	int	sockfd;
	int	revcount;
	char	msg[MSG_LEN];
	int 	retval;
	struct sockaddr_in serveraddr;
	//struct sockaddr_in clientaddr;

	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, "192.168.253.103", &serveraddr.sin_addr);
	serveraddr.sin_port = htons(SERV_PORT);

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		perror("socket");
		exit(1);
	} else {
		fprintf(stdout, "socket OK\n");
	}

	dg_cli(stdin, sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

	return 0;
}
