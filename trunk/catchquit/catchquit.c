#include "apue.h"

#define DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...) fprintf(stdout, fmt, ##args)
#else
#define dprintf(fmt, args...)
#endif
#define errprintf(fmt, args...) fprintf(stderr, fmt, ##args)

volatile sig_atomic_t	quitflag;

static void
sig_int(int signo)
{
	if (signo == SIGINT)
		printf("\ninterrupt\n");
	else if (signo == SIGQUIT)
		quitflag = 1;
}

int
main(int argc, char *argv[])
{
	sigset_t 	newmask, oldmask, zeromask;

	if (signal(SIGINT, sig_int) == SIG_ERR)
	{
		errprintf("signal SIGINT error\n");
		exit(1);
	}
	if (signal(SIGQUIT, sig_int) == SIG_ERR)
	{
		errprintf("signal SIGQUIT error\n");
		exit(1);
	}

	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);

	/*
	 *block quit adn save current signal mask
	 */
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
	{
		errprintf("sig_block error\n");
		exit(1);
	}

	while (quitflag == 0)
		sigsuspend(&zeromask);
	
	quitflag = 0;

	/*
	 *reset signal mask which unblocks quit
	 */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
	{
		errprintf("sigprocmask set error\n");
		exit(1);
	}
	exit(0);
}

