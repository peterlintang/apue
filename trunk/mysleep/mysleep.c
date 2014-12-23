#include "apue.h"

#define DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...) fprintf(stdout, fmt, ##args)
#else
#define dprintf(fmt, args...)
#endif
#define errprintf(fmt, args...) fprintf(stderr, fmt, ##args)


unsigned int sleep2(unsigned int nsecs);

int
main(int argc, char *argv[])
{
	dprintf("sleeping...\n");
	sleep2(2);
	dprintf("wake up from sleep\n");

	exit(0);

}

/*alarm process */
static void
sig_alam(int signo)
{
	/*do nothing*/
}

unsigned int
sleep2(unsigned int nsecs)
{
	if (signal(SIGALRM, sig_alam) == SIG_ERR)
	{
		return (nsecs);
	}
	alarm(nsecs);
	pause();
	return(alarm(0));
}
