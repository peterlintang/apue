#include "apue.h"
#include <pthread.h>

#define DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...) fprintf(stdout, fmt, ##args)
#else
#define dprintf(fmt, args...)
#endif
#define errprintf(fmt, args...) fprintf(stderr, fmt, ##args)


int		quitflag;
sigset_t 	mask;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  wait = PTHREAD_COND_INITIALIZER;

void *
thr_fn(void *arg)
{
	int err, signo;

	dprintf("cat interrupt thread id: %d\n", (int )pthread_self());
	dprintf("process id: %d\n", getpid());
	for (; ; )
	{
		err = sigwait(&mask, &signo);
		if (err != 0)
		{
			errprintf("sigwait failed\n");
			exit(1);
		}
		switch (signo)
		{
			case SIGINT:
				printf("\ninterrupt\n");
				break;
			case SIGQUIT:
				pthread_mutex_lock(&lock);
				quitflag = 1;
				pthread_mutex_unlock(&lock);
				pthread_cond_signal(&wait);
				return (0);
			default:
				printf("unexpected signal %d\n", signo);
				exit(1);

		}
	}
}


int
main(int argc, char *argv[])
{
	int		err;
	sigset_t	oldmask;
	pthread_t	tid;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);

	if ((err = pthread_sigmask(SIG_BLOCK, &mask, &oldmask)) != 0)
	{
		errprintf("pthread_sigmask SIG_BLOCK error!\n");
		exit(1);
	}


	err = pthread_create(&tid, NULL, thr_fn, 0);
	if (err != 0)
	{
		errprintf("pthread_create error\n");
		exit(1);
	}
	else
	{	
		dprintf("main thread id: %d\n", (int )pthread_self());
		dprintf("process id: %d\n", getpid());
	}


	pthread_mutex_lock(&lock);
	while (quitflag == 0)
	{
		pthread_cond_wait(&wait, &lock);
	}
	pthread_mutex_unlock(&lock);

	quitflag = 0;

	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
	{
		errprintf("SIG_SETMASK error\n");
		exit(1);
	}

	exit(0);
}


