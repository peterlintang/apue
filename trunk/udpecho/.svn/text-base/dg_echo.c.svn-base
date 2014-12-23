
/*
 *
 *
 */

#include <sys/types.h>
#include <sys/socket.h>

#define MSGLEN	4096


void dg_echo(int sockfd, struct sockaddr *pclientaddr, socklen_t clientlen)
{
	int	n;
	int	len;
	char	msg[MSGLEN];


	for ( ; ; ) {
		len = clientlen;
		n = recvfrom(sockfd, msg, MSGLEN, 0, pclientaddr, &len);
		sendto(sockfd, msg, n, 0, pclientaddr, len);
	}
}
