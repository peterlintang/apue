#include "apue.h"

#define DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...) fprintf(stdout, fmt, ##args)
#else
#define dprintf(fmt, args...)
#endif
#define errprintf(fmt, args...) fprintf(stderr, fmt, ##args)


int
main(int argc, char *argv[])
{
	int	n;
	int	fd[2];
	pid_t	pid;
	char *	line[MAXLINE];

	if (pipe(fd) < 0)
	{
		err_sys("pipe error");
	}
	dprintf("PIPE_BUF: %ld\n", fpathconf(fd[0], _PC_PIPE_BUF));
	if ((pid = fork()) < 0)
	{
		err_sys("fork error");
	}
	else if (pid > 0)
	{
		close(fd[0]);
		write(fd[1], "\nhello world\n", 13);
	}
	else
	{
		close(fd[1]);
		n = read(fd[0], line, MAXLINE);
		write(STDOUT_FILENO, line, n);
		sleep(35);
	}
	exit(0);
}
