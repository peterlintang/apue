#include "apue.h"
#include <setjmp.h>
#include <errno.h>


#define DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...) fprintf(stdout, fmt, ##args)
#else
#define dprintf(fmt, args...)
#endif
#define errprintf(fmt, args...) fprintf(stderr, fmt, ##args)


static void	sig_usr1(int signo), sig_alrm(int signo);
void pr_mask(const char *str);

static sigjmp_buf		jmpbuf;
static volatile sig_atomic_t 	canjump;

int
main(int argc, char *argv[])
{
	if (signal(SIGUSR1, sig_usr1) < 0)
	{
		errprintf("signal sigusr1 error\n");
		exit(1);
	}
	if (signal(SIGALRM, sig_alrm) < 0)
	{
		errprintf("signal sigalrm error\n");
		exit(1);
	}
	dprintf("starting main...\n");

	if (sigsetjmp(jmpbuf, 1))
	{
		dprintf("ending main.\n");
		exit(0);
	}
	canjump = 1;

	for (; ; )
		pause();
	
	dprintf("should not be here\n");
	exit(0);
}




static void
sig_usr1(int signo)
{
	time_t starttime;

	if (canjump == 0)
		return;
	
	pr_mask("starting sig_usr1: \n");
	alarm(3);
	starttime = time(NULL);
	for (; ; )
		if (time(NULL) > starttime + 5)
			break;
	pr_mask("finished sig_usr1: \n");

	canjump = 0;
	siglongjmp(jmpbuf, 1);
}


static void
sig_alrm(int signo)
{
	pr_mask("in sig_alrm: \n");
}

void 
pr_mask(const char *str)
{
	sigset_t	sigset;
	int		errno_save;

	errno_save = errno;
	if (sigprocmask(0, NULL, &sigset) < 0)
	{
		errprintf("sigprocmask error\n");
		exit(1);
	}
	printf("%s", str);
	if (sigismember(&sigset, SIGINT)) printf("SIGINT ");
	if (sigismember(&sigset, SIGQUIT)) printf("SIQUIT ");
	if (sigismember(&sigset, SIGUSR1)) printf("SIGUSR1 ");
	if (sigismember(&sigset, SIGALRM)) printf("SIGALRM ");
	printf("---\n");
	errno = errno_save;
}
















