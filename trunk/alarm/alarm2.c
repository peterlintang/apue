#include "apue.h"
#include <setjmp.h>

#define DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...) fprintf(stdout, fmt, ##args)
#else
#define dprintf(fmt, args...)
#endif
#define errprintf(fmt, args...) fprintf(stderr, fmt, ##args)

static void sig_alrm(int signo);
static jmp_buf env_alrm;

int
main(int argc, char *argv[])
{
	int 	n;
	char 	line[MAXLINE];

	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
	{
	//	perror("signal error!\n");
		errprintf("signal error!\n");
		exit(1);
	}
	if (setjmp(env_alrm) != 0)
	{
		//perror("read timeout!\n");
		errprintf("read timeout!\n");
		exit(1);
	}

	alarm(10);
	if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
	{
	//	perror("read error!\n");
		errprintf("read error!\n");
	}
	alarm(0);

	write(STDOUT_FILENO, line, n);
	exit(0);
}

static void
sig_alrm(int signo)
{
	longjmp(env_alrm, 1);
}
