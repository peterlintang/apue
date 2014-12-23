/*
 * test the semaphore
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define RESOURCE_NUM	4
#define THREADS_CREATE	8

void *get_sem_thread(void *arg)
{
	int	value;
	sem_t *sem = NULL;

	if (!arg) return NULL;

	sem = (sem_t *)arg;

	fprintf(stdout, "hello world \n");
	if (sem_wait(sem)) {
		fprintf(stderr, "unable to get sem\n");
		return NULL;
	}

	fprintf(stdout, "Ok thread %ld get a sem\n", pthread_self());
	sleep(2);
	sem_post(sem);
	sem_getvalue(sem, &value);
	fprintf(stdout, "current value: %d\n", value);
	fprintf(stdout, "thread %ld join\n", pthread_self());
	return NULL;
}

int main(int argc, char *argv[])
{
	int	i;
	int	ret = 0;
	sem_t	resource;
	pthread_t tid;

	if(sem_init(&resource, 0, RESOURCE_NUM)) {
		fprintf(stderr, "unable to initialize the semaphore\n");
		exit(1);
	}

	fprintf(stdout, "creating threads...\n");

	for (i = 0; i < THREADS_CREATE; i++) {
		if (pthread_create(&tid, NULL, get_sem_thread, &resource))
			fprintf(stderr, "create %d thread error\n", i);
		fprintf(stdout, "create %ld\n", tid);
	}

	sleep(10);
	sem_destroy(&resource);
	fprintf(stdout, "main exit\n");

	return ret;
}





