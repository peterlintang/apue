/*
 * my first echo server, it is so simple
 * the server will echo "hello world" to 
 * the client, once the client write to the server
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
	int	readcount;
	int 	writecount;
	int 	listenfd;
	int	acceptfd;
	char 	readbuf[4097];
	struct sockaddr_in seraddr;

	bzero(&seraddr, sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
//	inet_pton(AF_INET, "192.168.253.103", &seraddr.sin_addr);
	seraddr.sin_port = 3456;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0) {
		perror("socket");
		exit(1);
	}

	if (bind(listenfd, (struct sockaddr *)&seraddr, sizeof(seraddr))) {
		perror("bind");
		exit(2);
	} else {
		fprintf(stdout, "bind OK\n");
	}

	if (listen(listenfd, 4)) {
		perror("listen");
		exit(3);
	} else {
		fprintf(stdout, "listen OK\n");
	}

	while (1) {
		acceptfd = accept(listenfd, NULL, NULL);
		if (acceptfd < 0) {
			perror("accept");
			exit(4);
		} else {
			fprintf(stdout, "accept OK: %d\n", acceptfd);
		}

		while (1) {
			readcount = read(acceptfd, readbuf, 4096);
			if (readcount == 0) break;
			fprintf(stdout, "read count : %d\n", readcount);
//			puts(readbuf);
//			write(acceptfd, "hello world", strlen("hello world"));
			writecount = write(acceptfd, readbuf, readcount);
			fprintf(stdout, "write count : %d\n", writecount);
		}
		close(acceptfd);	/*should close accept fd once we dont need it */
	}

	close(listenfd);
	return 0;
}
