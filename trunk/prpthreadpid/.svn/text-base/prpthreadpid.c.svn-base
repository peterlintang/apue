/*
 *need to install libpthread in order to 
 *support pthread
 *
 */

#include "apue.h"
#include <pthread.h>

#define DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...) fprintf(stdout, fmt, ##args)
#else
#define dprintf(fmt, args...)
#endif
#define errprintf(fmt, args...) fprintf(stderr, fmt, ##args)


pthread_t 	ntid;

void
printids(const char *s)
{
	pid_t 		pid;
	pthread_t	tid;

	pid = getpid();
	tid = pthread_self();
	printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int )pid, \
		(unsigned int )tid, (unsigned int )tid);
}

void *
thr_fn(void *arg)
{
	printids("new thread: ");
	return ((void *)0);
}

int
main(int argc, char *argv[])
{
	int 	err;

	err = pthread_create(&ntid, NULL, thr_fn, NULL);
	if (err != 0)
	{
		errprintf("can't create thread: %s\n", strerror(err));
		exit(1);
	}

	printids("main thread: ");
	sleep(1);
	exit(0);
}




