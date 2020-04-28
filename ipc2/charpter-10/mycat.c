
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

#define BUFFSIZE	1024
#define NBUFF	8

struct {
	struct {
		char data[BUFFSIZE];
		ssize_t n;
	} buff[NBUFF];

	sem_t mutex;
	sem_t nempty;
	sem_t nstored;
} shared;

static int fd = 0;

static void *producer(void *arg)
{
	int i;

	for (i = 0; ; )
	{
		sem_wait(&shared.nempty);

		sem_wait(&shared.mutex);
		sem_post(&shared.mutex);

		shared.buff[i].n = read(fd, shared.buff[i].data, BUFFSIZE);
		if (shared.buff[i].n == 0)
		{
			sem_post(&shared.nstored);
			return NULL;
		}

		if (++i >= NBUFF)
			i = 0;
		sem_post(&shared.nstored);
	}

	return NULL;
}

static void *consumer(void *arg)
{
	int i;

	for (i = 0; ; )
	{
		sem_wait(&shared.nstored);

		sem_wait(&shared.mutex);
		sem_post(&shared.mutex);

		if (shared.buff[i].n == 0)
		{
			return NULL;
		}

		write(STDOUT_FILENO, shared.buff[i].data, shared.buff[i].n);
		if (++i >= NBUFF)
			i = 0;

		sem_post(&shared.nempty);
	}

	return NULL;
}

static void usage(const char *proc)
{
	fprintf(stdout, "usage: %s <pathname>\n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	int ret = 0;
	pthread_t tid_producer;
	pthread_t tid_consumer;

	if (argc != 2)
		usage(argv[0]);

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		fprintf(stderr, "%s open failed: %s\n", argv[1], strerror(errno));
		exit(1);
	}

	sem_init(&shared.mutex, 0, 1);
	sem_init(&shared.nempty, 0, NBUFF);
	sem_init(&shared.nstored, 0, 0);

	pthread_setconcurrency(2);

	pthread_create(&tid_producer, NULL, producer, NULL);
	pthread_create(&tid_consumer, NULL, consumer, NULL);

	pthread_join(tid_producer, NULL);
	pthread_join(tid_consumer, NULL);

	sem_destroy(&shared.mutex);
	sem_destroy(&shared.nstored);
	sem_destroy(&shared.nempty);

	return ret;
}



