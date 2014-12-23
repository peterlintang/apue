
/*
 *
 *
 *
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#define MSG_LEN 	4096

void dg_cli(FILE *fp, int sockfd, const struct sockaddr *pserveraddr, socklen_t servlen)
{
	int	n;
	char	sendline[MSG_LEN];
	char	recvline[MSG_LEN];

	while (fgets(sendline, MSG_LEN, fp) != NULL) {
		sendto(sockfd, sendline, strlen(sendline), 0, pserveraddr, servlen);
		n = recvfrom(sockfd, recvline, MSG_LEN, 0, NULL, NULL);
		recvline[n] = '\0';
		fputs(recvline, stdout);
	}
}
