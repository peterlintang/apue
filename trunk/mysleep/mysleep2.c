#include "apue.h"

#define DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...) fprintf(stdout, fmt, ##args)
#else
#define dprintf(fmt, args...)
#endif
#define errprintf(fmt, args...) fprintf(stderr, fmt, ##args)

unsigned int sleep2(unsigned int nsecs);
static void sig_int(int signo);

int
main(int argc, char *argv[])
{
	unsigned int unslept;

	if (signal(SIGINT, sig_int) == SIG_ERR)
	{
		perror("signal error!\n");
		exit(1);
	}
	dprintf("sleeping...\n");
	unslept = sleep2(5);
	dprintf("sleep2 returned: %d\n", unslept);
	exit(0);
}

static void 
sig_int(int signo)
{
	int 		i,j;
	volatile int 	x;

	dprintf("\nsig_int starting\n");
	for (i = 0; i < 3000000; i++)
		for (j = 0; j < 4000; j++)
			x += i + j;
	dprintf("sig_int finished\n");
}
