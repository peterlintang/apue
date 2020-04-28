

/**
 *
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>


#define MAXLINE	1024

#define SERVER_FIFO	"/tmp/server_fifo"


#define FILE_MODE	S_IRUSR | S_IWUSR


int main(int argc, char *argv[])
{
	int n;
	int len;
	int readfd;
	int writefd;
	char buff[MAXLINE];
	char fifoname[MAXLINE];
	char *ptr;
	pid_t	pid;

	pid = getpid();

	snprintf(fifoname, sizeof(fifoname), "/tmp/fifo.%ld", (long)pid);
	mkfifo(fifoname, FILE_MODE);

	snprintf(buff, sizeof(buff), "%ld ", (long)pid);
	len = strlen(buff);
	ptr = buff + len;

	fgets(ptr, MAXLINE - len, stdin);

	writefd = open(SERVER_FIFO, O_WRONLY);
	write(writefd, buff, strlen(buff));

	readfd = open(fifoname, O_RDONLY);		// will block until someone open fifo1 for write
	while ((n = read(readfd, buff, MAXLINE)) > 0)
		write(STDOUT_FILENO, buff, n);

	close(readfd);
	close(writefd);
	unlink(fifoname);

	return 0;
}

