
/*
 * 多个生产者，单个消费者，使用基于内存的信号灯
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#define NBUFF		10
#define MAXTHREADS	100
#define SEM_MUTEX	"/mutex"
#define SEM_NEMPTY	"/nempty"
#define SEM_NSTORED	"/nstored"

#define min(x, y)		(x) > (y) ? (y) : (x)

#define PX_IPC_NAME(mutex)	"/hello/" mutex

static int nitems = NBUFF;
static int nthreads = MAXTHREADS;

struct {
	int buff[NBUFF];
	int input;
	int inputval;
	sem_t mutex; // 保护临界区
	sem_t nempty;
	sem_t nstored;
} shared;

static void *producer(void *arg)
{
	int i;

//	for (i = 0; i < nitems; i++)
	for ( ; ; )
	{
		sem_wait(&shared.nempty);
		sem_wait(&shared.mutex);

		if (shared.input >= nitems)
		{
			sem_post(&shared.nempty);
			sem_post(&shared.mutex);
			return (NULL);
		}

		shared.buff[shared.input % NBUFF] = shared.inputval;
		shared.input++;
		shared.inputval++;

		sem_post(&shared.mutex);
		sem_post(&shared.nstored);
		*((int *)arg) += 1;
	}

	return NULL;
}

static void *consumer(void *arg)
{
	int i;

	for (i = 0; i < nitems; i++)
	{
		sem_wait(&shared.nstored);
		sem_wait(&shared.mutex);
		if (shared.buff[i % NBUFF] != i)
			fprintf(stderr, "buff[%d] = %d\n", i, shared.buff[i % NBUFF]);
		sem_post(&shared.mutex);
		sem_post(&shared.nempty);
	}

	return NULL;
}

static void usage(char *proc)
{
	fprintf(stdout, "usage: %s #items #threads\n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	int i;
	int ret;
	int count[MAXTHREADS];
	pthread_t tid_producer[MAXTHREADS];
	pthread_t tid_consumer;

	if (argc != 3)
		usage(argv[0]);

	nitems = atoi(argv[1]);
	nthreads = min(atoi(argv[2]), MAXTHREADS);

	ret = sem_init(&shared.mutex, 0, 1);
	if (0 != ret)
	{
		fprintf(stderr, "init mutex failed: %s\n", strerror(errno));
		exit(1);
	}
	ret = sem_init(&shared.nempty, 0, NBUFF);
	if (0 != ret)
	{
		fprintf(stderr, "init nempty failed: %s\n", strerror(errno));
		exit(1);
	}
	ret = sem_init(&shared.nstored, 0, 0);
	if (0 != ret)
	{
		fprintf(stderr, "init nstored failed: %s\n", strerror(errno));
		exit(1);
	}

	pthread_setconcurrency(nthreads + 1);

	for (i = 0; i < nthreads; i++)
	{
		count[i] = 0;
		pthread_create(&tid_producer[i], NULL, producer, &count[i]);
	}

	pthread_create(&tid_consumer, NULL, consumer, NULL);

	for (i = 0; i < nthreads; i++)
	{
		pthread_join(tid_producer[i], NULL);
		fprintf(stdout, "count[%d] = %d\n", i, count[i]);
	}

	pthread_join(tid_consumer, NULL);

	sem_destroy(&shared.mutex);
	sem_destroy(&shared.nempty);
	sem_destroy(&shared.nstored);

	return 0;
}





