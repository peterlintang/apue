
/*
 * 使用基于内存的信号灯
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
#define SEM_MUTEX	"/mutex"
#define SEM_NEMPTY	"/nempty"
#define SEM_NSTORED	"/nstored"

#define PX_IPC_NAME(mutex)	"/hello/" mutex

static int nitems = NBUFF;

struct {
	int buff[NBUFF];
	sem_t mutex; // 保护临界区
	sem_t nempty;
	sem_t nstored;
} shared;

static void *producer(void *arg)
{
	int i;

	for (i = 0; i < nitems; i++)
	{
		sem_wait(&shared.nempty);
		sem_wait(&shared.mutex);
		shared.buff[i % NBUFF] = i;
		sem_post(&shared.mutex);
		sem_post(&shared.nstored);
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
	fprintf(stdout, "usage: %s #items\n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	int ret;
	pthread_t tid_producer;
	pthread_t tid_consumer;

	if (argc != 2)
		usage(argv[0]);

	nitems = atoi(argv[1]);

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

	pthread_setconcurrency(2);

	pthread_create(&tid_producer, NULL, producer, NULL);
	pthread_create(&tid_consumer, NULL, consumer, NULL);

	pthread_join(tid_producer, NULL);
	pthread_join(tid_consumer, NULL);

	sem_destroy(&shared.mutex);
	sem_destroy(&shared.nempty);
	sem_destroy(&shared.nstored);

	return 0;
}





