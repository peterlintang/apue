#include "apue.h"
#include <pthread.h>
#include <time.h>
#include <sys/time.h>


#define DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...) fprintf(stdout, fmt, ##args)
#else
#define dprintf(fmt, args...)
#endif
#define errprintf(fmt, args...) fprintf(stderr, fmt, ##args)


extern int makepthread(void *(*)(void *), void *);

struct to_info {
	void 	(*to_fn)(void *);
	void 	*to_arg;
	struct 	timespec 	to_wait;
};

#define SECTONSEC	1000000000
#define USECTONSEC	1000

void *
timeout_helper(void *arg)
{
	struct to_info	*tip;

	tip = (struct to_info *)arg;
	dprintf("sleeping \n");
	nanosleep(&tip->to_wait, NULL);
	dprintf("call funcion do the job\n");
	(tip->to_fn)(tip->to_arg);
	return (0);
}

void
timeout(const struct timespec *when, void (*func)(void *), void *arg)
{
	struct timespec	now;
	struct timeval	tv;
	struct to_info	*tip;
	int		err;

	gettimeofday(&tv, NULL);
	now.tv_sec = tv.tv_sec;
	now.tv_nsec = tv.tv_usec * USECTONSEC;
	if ((when->tv_sec > now.tv_sec) \
		|| (when->tv_sec == now.tv_sec && when->tv_nsec > now.tv_nsec))
	{
		tip = malloc(sizeof(struct to_info));
		if (tip != NULL)
		{
			tip->to_fn = func;
			tip->to_arg = arg;
			tip->to_wait.tv_sec = when->tv_sec - now.tv_sec;
			if (when->tv_nsec >= now.tv_nsec)
			{
				tip->to_wait.tv_nsec = when->tv_nsec - now.tv_nsec;
			}
			else
			{
				tip->to_wait.tv_sec--;
				tip->to_wait.tv_nsec = SECTONSEC - now.tv_nsec + when->tv_nsec;
			}
			dprintf("making thread\n");
			err = makethread(timeout_helper, (void *)tip);
			if (err == 0)
			{
				dprintf("make done\n");
				return ;
			}
		}
	}
	(*func)(arg);

}

pthread_mutexattr_t	attr;
pthread_mutex_t		mutex;

void
retry(void *arg)
{
	dprintf("second lock mutex\n");
	/*
	 *only after the main thread unlock the mutex
	 *can we lock it.
	 */
	pthread_mutex_lock(&mutex);
	/*perform retry steps.... do nothing*/
	fprintf(stderr, "in retry\n");
	pthread_mutex_unlock(&mutex);
	dprintf("unlock mutex from retry\n");
}

int
main(int argc, char *argv[])
{
	int		err, condition, arg;
	struct timespec when;
	struct timeval	timeval;

//	condition = 1;
	gettimeofday(&timeval, NULL);
	when.tv_sec = timeval.tv_sec + 2;
	when.tv_nsec = timeval.tv_usec * USECTONSEC ;

	if ((err = pthread_mutexattr_init(&attr)) != 0)
	{
		errprintf("pthread_mutexattr_init failed!\n");
		exit(1);
	}
	if ((err = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE)) != 0)
	{
		errprintf("pthread_mutexattr_settype failed!\n");
		exit(1);
	}
	if ((err = pthread_mutex_init(&mutex, &attr)) != 0)
	{
		errprintf("pthread_mutex_init failed!\n");
		exit(1);
	}

	pthread_mutex_lock(&mutex);

	if (condition)
	{
		timeout(&when, retry, (void *)arg);
	}
	sleep(4);
	
	pthread_mutex_unlock(&mutex);
	/*
	 *wait for created thread to finish his job
	 *else the thread will be exit
	 */
	sleep(8);
	exit(0);
}


