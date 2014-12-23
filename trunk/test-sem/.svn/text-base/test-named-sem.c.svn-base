/*
 * test the named semaphore
 * see /usr/include/semaphore.h	for details
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

#define RESOURCE_NUM	4
#define THREADS_CREATE	8

void *get_sem_thread(void *arg)
{
	int	value;
	sem_t *sem = NULL;

/*
	if (!arg) return NULL;

	sem = (sem_t *)arg;
*/
	pthread_detach(pthread_self());

//	sem = sem_open("/johnlin's-named-sem", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, RESOURCE_NUM);
	sem = sem_open("/johnlin's-named-sem", O_RDWR);
	if (sem == SEM_FAILED) {
		fprintf(stdout, "<%s:%s> failed \n", __FILE__, __func__);
		pthread_exit(NULL);
	}
//	fprintf(stdout, "sem addr: %p\n", sem);

	fprintf(stdout, "hello world \n");
	if (sem_wait(sem)) {
		fprintf(stderr, "unable to get sem\n");
		return NULL;
	}
	sem_getvalue(sem, &value);
	fprintf(stdout, "get resource, current value: %d\n", value);
	sleep(1);

//	fprintf(stdout, "Ok thread %ld get a sem\n", pthread_self());
//	sleep(2);
	sem_post(sem);
	sem_close(sem);
//	fprintf(stdout, "thread %ld post a sem\n", pthread_self());
	return NULL;
}

int main(int argc, char *argv[])
{
	int	i;
	int	ret = 0;
	sem_t	*resource;
	pthread_t tid;

	resource = sem_open("/johnlin's-named-sem", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, RESOURCE_NUM);
	if (resource == SEM_FAILED) {
		perror("sem_open");
		exit(1);
	}
//	fprintf(stdout, "sem addr: %p\n", resource);

	fprintf(stdout, "creating threads...\n");

	for (i = 0; i < THREADS_CREATE; i++) {
		if (pthread_create(&tid, NULL, get_sem_thread, &resource))
			fprintf(stderr, "create %d thread error\n", i);
		fprintf(stdout, "create %ld\n", tid);
	}

	sleep(10);
	sem_close(resource);
	sem_unlink("/johnlin's-named-sem");	// remove the sem
	fprintf(stdout, "main exit\n");

	return ret;
}





