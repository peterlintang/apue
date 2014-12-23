#include "apue.h"
#include <signal.h>
#include <errno.h>

#define DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...) fprintf(stdout, fmt, ##args)
#else
#define dprintf(fmt, args...)
#endif
#define errprintf(fmt, args...) fprintf(stderr, fmt, ##args)

static void sig_quit(int signo);

void
pr_mask(const char *str)
{
	sigset_t	sigset;
	int		errno_save;

	errno_save = errno;
	if (sigprocmask(0, NULL, &sigset) < 0)
	{
		errprintf("sigprocmask error!\n");
		exit(1);
	}

	printf("%s:", str);

	if (sigismember(&sigset, SIGINT))	
		dprintf("SIGINT ");
	if (sigismember(&sigset, SIGQUIT))	 
		dprintf("SIGQUIT ");
	if (sigismember(&sigset, SIGUSR1))	 
		dprintf("SIGUSR1 ");
	if (sigismember(&sigset, SIGALRM))	 
		dprintf("SIGALRM ");

	printf("\n");
	errno = errno_save;
}

int 
main(int argc, char *argv[])
{
	sigset_t newmask, oldmask, pendmask;

	if (signal(SIGQUIT, sig_quit) == SIG_ERR)
	{
		errprintf("signal error\n");
		exit(1);
	}

	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);

	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
	{
		errprintf("SIG_BLOCK error\n");
		exit(1);
	}

//	raise(SIGQUIT);
	sleep(5);

	if (sigpending(&pendmask) < 0)
	{
		errprintf("sigpending error\n");
		exit(1);
	}
	if (sigismember(&pendmask, SIGQUIT))
		dprintf("\nSIGQUIT pending\n");

	if (sigismember(&newmask, SIGQUIT))
		dprintf("\nSIGQUIT \n");

	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
	{
		errprintf("SIG_SETMAKS error\n");
		exit(1);
	}
	dprintf("SIGQUIT unblocked\n");

	sleep(5);
	
	exit(0);
}

static void
sig_quit(int signo)
{
	dprintf("catch a quit\n");
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
	{
		errprintf("can't reset SIGQUIT\n");
		exit(1);
	}
}



