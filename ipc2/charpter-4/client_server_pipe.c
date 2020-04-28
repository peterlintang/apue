

/**
 *
 * 创建两条管道，一个进程负责从标准输入中获取文件名称，然后通过
 * 一条管道将文件名称发给另一进程；另一进程从管道获取文件名称后，
 * 打开文件并将文件内容通过另一管道发给前一进程，若出错，将错误信息
 * 返回给前一进程；
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

void client(int , int);
void server(int , int);

int main(int argc, char *argv[])
{
	int pipe1[2];
	int pipe2[2];
	pid_t childpid;

	pipe(pipe1);
	pipe(pipe2);

	if ((childpid = fork()) == 0)
	{
		close(pipe1[1]);
		close(pipe2[0]);

		server(pipe1[0], pipe2[1]);
		exit(0);
	}

	close(pipe1[0]);
	close(pipe2[1]);

	client(pipe2[0], pipe1[1]);
	waitpid(childpid, NULL, 0);
	exit(0);
	return 0;
}

void client(int readfd, int writefd)
{
	size_t len = 0;
	size_t n = 0;
	char buf[MAXLINE];

	fgets(buf, MAXLINE, stdin);
	len = strlen(buf);
	if (buf[len - 1] == '\n')
		len--;

	write(writefd, buf, len);

	while ((n = read(readfd, buf, MAXLINE)) > 0)
		write(STDOUT_FILENO, buf, n);
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





