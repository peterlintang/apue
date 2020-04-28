
/*
 * 使用有名信号灯
 *
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
	sem_t *mutex; // 保护临界区
	sem_t *nempty;
	sem_t *nstored;
} shared;

static void *producer(void *arg)
{
	int i;

	for (i = 0; i < nitems; i++)
	{
		sem_wait(shared.nempty);
		sem_wait(shared.mutex);
		shared.buff[i % NBUFF] = i;
		sem_post(shared.mutex);
		sem_post(shared.nstored);
	}

	return NULL;
}

static void *consumer(void *arg)
{
	int i;

	for (i = 0; i < nitems; i++)
	{
		sem_wait(shared.nstored);
		sem_wait(shared.mutex);
		if (shared.buff[i % NBUFF] != i)
			fprintf(stderr, "buff[%d] = %d\n", i, shared.buff[i % NBUFF]);
		sem_post(shared.mutex);
		sem_post(shared.nempty);
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
	pthread_t tid_producer;
	pthread_t tid_consumer;

	if (argc != 2)
		usage(argv[0]);

	nitems = atoi(argv[1]);

	sem_unlink((SEM_MUTEX));
	sem_unlink((SEM_NEMPTY));
	sem_unlink((SEM_NSTORED));

	shared.mutex = sem_open((SEM_MUTEX), O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
	if (shared.mutex == SEM_FAILED)
	{
		fprintf(stderr, "%s failed to open: %s\n", (SEM_MUTEX), strerror(errno));
		exit(1);
	}
	shared.nempty = sem_open((SEM_NEMPTY), O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, NBUFF);
	if (shared.mutex == SEM_FAILED)
	{
		fprintf(stderr, "%s failed to open: %s\n", (SEM_NEMPTY), strerror(errno));
		exit(1);
	}
	shared.nstored = sem_open((SEM_NSTORED), O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
	if (shared.mutex == SEM_FAILED)
	{
		fprintf(stderr, "%s failed to open: %s\n", (SEM_NSTORED), strerror(errno));
		exit(1);
	}

	pthread_setconcurrency(2);

	pthread_create(&tid_producer, NULL, producer, NULL);
	pthread_create(&tid_consumer, NULL, consumer, NULL);

	pthread_join(tid_producer, NULL);
	pthread_join(tid_consumer, NULL);

	sem_close(shared.mutex);
	sem_close(shared.nempty);
	sem_close(shared.nstored);

	sem_unlink((SEM_MUTEX));
	sem_unlink((SEM_NEMPTY));
	sem_unlink((SEM_NSTORED));

	return 0;
}





