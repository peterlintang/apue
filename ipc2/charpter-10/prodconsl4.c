
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
#define CONMAXTHREADS	100
#define SEM_MUTEX	"/mutex"
#define SEM_NEMPTY	"/nempty"
#define SEM_NSTORED	"/nstored"

#define min(x, y)		(x) > (y) ? (y) : (x)

#define PX_IPC_NAME(mutex)	"/hello/" mutex

static int nitems = NBUFF;
static int nthreads = MAXTHREADS;
static int nconthreads = CONMAXTHREADS;

struct {
	int buff[NBUFF];
	int input;		// 生产者用
	int inputval;
	int con_index;	// 消费者用
	int con_indexval;
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
			sem_post(&shared.nstored);		//按照书上说的在这加上一行也可以，消费者线程可以据此退出，而不堵塞
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

//	for (i = 0; i < nitems; i++)
	for ( ; ; )
	{
		sem_wait(&shared.nstored);
		sem_wait(&shared.mutex);

		if (shared.con_index >= nitems)
		{
			sem_post(&shared.nstored);
			sem_post(&shared.mutex);
			return NULL;
		}

		if (shared.buff[shared.con_index  % NBUFF] != shared.con_indexval)
			fprintf(stderr, "buff[%d] = %d, %d\n", shared.con_index, 
							shared.buff[shared.con_index % NBUFF],
							shared.con_indexval);
		shared.con_index++;
		shared.con_indexval++;

		/*
		*((int *)arg) += 1;
		if (shared.con_index >= nitems)
		{
			sem_post(&shared.nstored);
			sem_post(&shared.nempty);
			sem_post(&shared.mutex);
			return NULL;
		}
		*/

		sem_post(&shared.mutex);
		sem_post(&shared.nempty);
		*((int *)arg) += 1;
	}

	return NULL;
}

static void usage(char *proc)
{
	fprintf(stdout, "usage: %s #items #prothreads #conthreads\n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	int i;
	int ret;
	int count[MAXTHREADS];
	int con_count[CONMAXTHREADS];	
	pthread_t tid_producer[MAXTHREADS];
	pthread_t tid_consumer[CONMAXTHREADS];

	if (argc != 4)
		usage(argv[0]);

	nitems = atoi(argv[1]);
	nthreads = min(atoi(argv[2]), MAXTHREADS);
	nconthreads = min(atoi(argv[3]), CONMAXTHREADS);

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

	pthread_setconcurrency(nthreads + nconthreads);

	for (i = 0; i < nthreads; i++)
	{
		count[i] = 0;
		pthread_create(&tid_producer[i], NULL, producer, &count[i]);
	}

	for (i = 0; i < nconthreads; i++)
	{
		con_count[i] = 0;
		pthread_create(&tid_consumer[i], NULL, consumer, &con_count[i]);
	}

	for (i = 0; i < nthreads; i++)
	{
		pthread_join(tid_producer[i], NULL);
		fprintf(stdout, "count[%d] = %d\n", i, count[i]);
	}

	for (i = 0; i < nconthreads; i++)
	{
		pthread_join(tid_consumer[i], NULL);
		fprintf(stdout, "concount[%d] = %d\n", i, con_count[i]);
	}

	sem_destroy(&shared.mutex);
	sem_destroy(&shared.nempty);
	sem_destroy(&shared.nstored);

	return 0;
}





