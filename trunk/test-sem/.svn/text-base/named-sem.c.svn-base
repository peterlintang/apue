
/*
 * implements the named semphore for
 * processes usage
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>


#include "named-sem.h"

int create_named_sem(const char *pathname, int oflags, int res_num)
{
	sem_t	*sem = NULL;

	if (!pathname || res_num < 0) {
		fprintf(stderr, "<%s> arguments error\n", __func__);
		return -2;
	}

	oflags |= (O_CREAT | O_EXCL | O_RDWR);
	sem = sem_open(pathname, oflags, CREATE_MODE, res_num);
	if (sem == SEM_FAILED) {
		perror("sem_open");
		return -1;
	}

	sem_close(sem);
	fprintf(stdout, "<%s> pathname: %s, res_num: %d , sem created\n",
			__func__, pathname, res_num);

	return 0;
}


int destroy_named_sem(const char *pathname)
{
	if (!pathname) {
		fprintf(stderr, "<%s> arguments error\n", __func__);
		return -1;
	}

	sem_unlink(pathname);
	fprintf(stdout, "<%s> destroy named sem: %s\n", 
			__func__, pathname);
	return 0;
}


named_sem_t *open_named_sem(const char *pathname)
{
	named_sem_t *nsem = NULL;

	if (!pathname) {
		fprintf(stdout, "<%s> arguments error\n", __func__);
		return NULL;
	}

	if (!(nsem = calloc(1, sizeof(*nsem)))) {
		perror("calloc");
		return NULL;
	}

	if (!(nsem->name = strdup(pathname))) {
		perror("strdup");
		free(nsem);
		return NULL;
	}

	if ((nsem->sem = sem_open(nsem->name, O_RDWR)) == SEM_FAILED) {
		perror("sem_open");
		free(nsem->name);
		free(nsem);
		return NULL;
	}

	fprintf(stdout, "<%s> open sem: %s\n", __func__, nsem->name);
	return nsem;
}

void close_named_sem(named_sem_t **ppsem)
{
	named_sem_t *sem = NULL;

	if (ppsem && *ppsem) {
		sem = *ppsem;
		fprintf(stdout, "<%s> close named sem: %s\n", 
				__func__, sem->name);
		if (sem->sem) {
			fprintf(stdout, "<%s> close it\n", __func__);
			sem_close(sem->sem);
		}
		free(sem->name);
		free(sem);
		*ppsem = NULL;
	}
}

int wait_named_sem(named_sem_t *psem, int nonblock)
{
	if (!psem || !psem->sem) {
		fprintf(stderr, "<%s> argumetns error\n", __func__);
		return -2;
	}

	if (nonblock) {
		fprintf(stdout, "<%s> try non block wait\n", __func__);
		return sem_trywait(psem->sem);
	}

	fprintf(stdout, "<%s> wait sem\n", __func__);
	return sem_wait(psem->sem);
}

int post_named_sem(named_sem_t *psem)
{
	if (!psem || !psem->sem) {
		fprintf(stderr, "<%s> argumetns error\n", __func__);
		return -2;
	}
	
	return sem_post(psem->sem);
}







