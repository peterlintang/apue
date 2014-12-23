/*
 * my first echo server, it is so simple
 * the server will echo "hello world" to 
 * the client, once the client write to the server
 */

/* 
 * second
 * conoccurence for client to connect, for each client connect
 * to the server, we fork a child process to server the client
 *
 */

/*
 * third
 * add signal SIGCHLD handler, deal with exited child processes
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
//#include <sys/stat.h>	
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void signal_child(int signo)
{
	static int signal_count = 0;
	fprintf(stdout, "get signal SIGCHLD : %d\n", ++signal_count);
	fprintf(stdout, "exited child : %d\n",waitpid(-1, NULL, 0));
}

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
	seraddr.sin_port = 3456;

	if (signal(SIGCHLD, signal_child) == SIG_ERR) {
		perror("signal");
		exit(5);
	}

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
			continue;
	//		exit(4);
		} else {
			fprintf(stdout, "accept OK: %d\n", acceptfd);
		}

		/* child */
		if (fork() == 0) {
			fprintf(stdout, "in child , srving client\n");
			close(listenfd);
			while (1) {
				readcount = read(acceptfd, readbuf, 4096);
				if (readcount == 0) break;
				fprintf(stdout, "read count : %d\n", readcount);
	//			puts(readbuf);
	//			write(acceptfd, "hello world", strlen("hello world"));
				writecount = write(acceptfd, readbuf, readcount);
				fprintf(stdout, "write count : %d\n", writecount);
			}
			close(acceptfd);
			exit(0);
		}

		/* parent */
		close(acceptfd);	/*should close accept fd once we dont need it */
	}

	close(listenfd);
	return 0;
}
