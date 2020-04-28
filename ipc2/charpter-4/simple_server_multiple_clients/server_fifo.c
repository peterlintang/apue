

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

void client(int , int);
void server(int , int);

int main(int argc, char *argv[])
{
	int n;
	int fd;
	int readfd;
	int dummyfd;
	int writefifo;
	char *ptr;
	char buff[MAXLINE];
	char fifoname[MAXLINE];
	pid_t pid;

	unlink(SERVER_FIFO);

	mkfifo(SERVER_FIFO, FILE_MODE);

	readfd = open(SERVER_FIFO, O_RDONLY);		// will block until someone open fifo1 for write
	dummyfd = open(SERVER_FIFO, O_WRONLY);

	while ((n = read(readfd, buff, MAXLINE)) > 0)
	{
		if (buff[n - 1] == '\n')
		{
			n--;
		}
		buff[n] = '\0';

		if ((ptr = strchr(buff, ' ')) == NULL)
		{
			fprintf(stderr, "no pid\n");
			continue;
		}
		*ptr++ = '\0';

		pid = atoi(buff);
		snprintf(fifoname, sizeof(fifoname), "/tmp/fifo.%ld", (long)pid);

		if ((writefifo = open(fifoname, O_WRONLY)) < 0)
		{
			fprintf(stderr, "open %s failed\n", fifoname);
			continue;
		}

		if ((fd = open(ptr, O_RDONLY)) < 0)
		{
			snprintf(buff + n, sizeof(buff) - n, ":cant open: %s\n", strerror(errno));
			n = strlen(ptr);
			write(writefifo, ptr, n);
			close(writefifo);
		}
		else
		{
			while ((n = read(fd, buff, MAXLINE)) > 0)
				write(writefifo, buff, n);
			close(fd);
			close(writefifo);
		}
	}

	close(readfd);
	close(dummyfd);
	unlink(SERVER_FIFO);

	return 0;
}


void server(int readfd, int writefd)
{
	size_t n;
	int fd;
	char buf[MAXLINE + 1];

	if ((n = read(readfd, buf, MAXLINE)) == 0)
		exit(1);

	buf[n] = '\0';

	if ((fd = open(buf, O_RDONLY)) < 0)
	{
		snprintf(buf + n, sizeof(buf) - n, ": cannt open, %s\n", strerror(errno));
		n = strlen(buf);
		write(writefd, buf, n);
	}
	else
	{
		while ((n = read(fd, buf, MAXLINE)) > 0)
			write(writefd, buf, n);
		close(fd);
	}
}





