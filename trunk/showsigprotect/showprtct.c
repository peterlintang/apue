#include "apue.h"

#define DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...) fprintf(stdout, fmt, ##args)
#else
#define dprintf(fmt, args...)
#endif
#define errprintf(fmt, args...) fprintf(stderr, fmt, ##args)

static void sig_int(int signo);

int
main(int argc, char *argv[])
{
	sigset_t 	newmask, oldmask, waitmask;

	pr_mask("program start: ");

	if (signal(SIGINT, sig_int) == SIG_ERR)
	{
		errprintf("signal (SIGINT) error\n");
		exit(1);
	}

	sigemptyset(&waitmask);
	sigaddset(&waitmask, SIGUSR1);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);

	/*
	 *block SIGINT and save current signal mask
	 */
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
	{
		errprintf("sigprocmask error\n");
		exit(1);
	}

	pr_mask("in critical region: ");
	if (sigsuspend(&waitmask) != -1)
	{
		errprintf("sigsuspend error\n");
		exit(1);
	}
	pr_mask("after return from sigsuspend: ");

	/*
	 *reset signal mask which unblocks SIGINT
	 */

	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
	{
		errprintf("sigprocmask set error\n");
		exit(1);
	}

	pr_mask("program exit: ");
	exit(0);
}

static void
sig_int(int signo)
{
	pr_mask("\nin sig_int: ");
}
