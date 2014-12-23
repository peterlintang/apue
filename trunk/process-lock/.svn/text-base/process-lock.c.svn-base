/************************************************************
 *	file		:	process-lock.c
 *	author		:	john lin
 *	date		:	Wed Aug 15 20:32:49 PDT 2012
 *	desc		:	implement the interfaces of 
 *				processes shared memory lock
 *				and condition
 *
 * copyright (c) john lin
 *************************************************************/

/*
 * implements the interfaces of processes' lock
 * using shared memory
 * filename:	process-lock.c
 */

#include <stdio.h>
#include <stdlib.h>

#include "process-lock.h"

/*
 * create a new processes shared memory for pthread lock & cond
 * @pathname
 * @id			these two is used for create shared memory
 * return value:
 * 		NULL		error
 * 		pointer	to the shared memory in the process address
 */
void *create_process_lock(const char *pathname, int id)
{
	int	flags = 0;
	key_t	key;
	int	shmid;
	void	*shmaddr 	 = NULL;
	process_lock_t *lockaddr = NULL;
	pthread_mutexattr_t attr;
	pthread_condattr_t cond_attr;

	if (!pathname) {
		fprintf(stderr, "arguments error\n");
		return NULL;
	}

	if ((key = ftok(pathname, id)) == -1) {
		perror("ftok");
		return NULL;
	}

	/*
	 * shmget -- system v ipc
	 */
//	flags = (IPC_CREAT | IPC_EXCL | SHM_R | SHM_W);
	flags = (IPC_CREAT | SHM_R | SHM_W);
	if (((shmid = shmget(key, sizeof(process_lock_t), flags)) == -1) &&
			errno == EEXIST) {
		fprintf(stdout, "shared memory path: %s, id: %d exist\n", 
				pathname, id);
		return NULL;
	}

	if ((shmaddr = shmat(shmid, shmaddr, SHM_R | SHM_W)) == (void *)-1) {
		perror("shmat");
		shmctl(shmid, IPC_RMID, 0);
		return NULL;
	}

	lockaddr = (process_lock_t *)shmaddr;
        pthread_mutexattr_init(&attr);
        pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
        pthread_mutex_init(&lockaddr->lock, &attr);
        pthread_mutexattr_destroy(&attr);
	pthread_condattr_init(&cond_attr);
	pthread_condattr_setpshared(&cond_attr, PTHREAD_PROCESS_SHARED);
	pthread_cond_init(&lockaddr->cond, &cond_attr);
	pthread_condattr_destroy(&cond_attr);
	pthread_mutex_lock(&lockaddr->lock);
	lockaddr->shmid = shmid;
	lockaddr->count = 1;
	pthread_mutex_unlock(&lockaddr->lock);
//	lockadd->status	= 0;

	fprintf(stdout, "create shared memory, key: %d, path: %s, id: %d\n",
			key, pathname, id);
//	shmdt(shmaddr);
	return shmaddr;
}

/*
 * destroy the shared memory for pthread lock & cond
 * @pshmaddr	the pointer point to the shared memory's pointer
 * return value:
 * 		-2	arguments error
 * 		-1	someone is using the shared memory
 * 		0	ok
 */
int destroy_process_lock(void **pshmaddr)
{
	process_lock_t *plock = NULL;

	if (pshmaddr && *pshmaddr) {
		plock = *pshmaddr;
		pthread_mutex_lock(&plock->lock);
		if (!(--plock->count)) {
//			plock->status = 1;
			pthread_mutex_unlock(&plock->lock);
			fprintf(stdout, "destroying shared memory\n");
			pthread_mutex_destroy(&plock->lock);
			pthread_cond_destroy(&plock->cond);
			shmctl(plock->shmid, IPC_RMID, 0);
			shmdt(plock);
			fprintf(stdout, "done\n");
			return 0;
		} else {
			pthread_mutex_unlock(&plock->lock);
			fprintf(stderr, "try to destroy shared memory while others are accessing\n");
			return -1;
		}
	}

	return -2;
}

/*
 * map the shared memory to the caller's address space
 * return value:
 * 		NULL	error
 * 		pointer to the shared memory	success
 */
void *map_process_lock(const char *pathname, int id)
{
	key_t	key;
	int	flags = 0;
	int	shmid;
	void	*shmaddr = NULL;
	process_lock_t *plock = NULL;

	if (!pathname) {
		fprintf(stderr, "arguments error\n");
		return NULL;
	}

	if ((key = ftok(pathname, id)) == -1) {
		perror("ftok");
		return NULL;
	}
	
	flags = (SHM_R | SHM_W);
	if ((shmid = shmget(key, sizeof(process_lock_t), flags)) == -1) {
		perror("shmget");
		return NULL;
	}

	if ((shmaddr = shmat(shmid, shmaddr, SHM_R | SHM_W)) == (void *)-1) {
		perror("shmat");
		shmctl(shmid, IPC_RMID, 0);
		return NULL;
	}

	plock = (process_lock_t *)shmaddr;
	pthread_mutex_lock(&plock->lock);
	plock->count++;
	pthread_mutex_unlock(&plock->lock);

	fprintf(stdout, "mapp shared memory ok, open count: %d\n", 
			plock->count);
	return plock;
}

/*
 * unmap the shared memory from process's space
 * return value:
 * 		0	success
 * 		-1	arguments error
 */
int unmap_process_lock(void **pshm)
{
	process_lock_t *plock = NULL;

	if (pshm && *pshm) {
		plock = *pshm;
		pthread_mutex_lock(&plock->lock);
		fprintf(stdout, "unmapping shared memory, open count: %d\n", 
			plock->count);
		plock->count--;
		pthread_mutex_unlock(&plock->lock);
		shmdt(plock);
		fprintf(stdout, "done\n");
		return 0;
	}

	return -1;
}

/*
 * get the processes shared lock
 * return value
 * 		-1	arguments error
 * 		0	ok
 */
int get_process_lock(void *plock)
{
	process_lock_t *lock = plock;

	if (!lock) return -1;

	fprintf(stdout, "<%s> get lock\n", __func__);
	pthread_mutex_lock(&lock->lock);

	return 0;
}

/*
 * release the processes shared lock
 * return value
 * 		-1	arguments error
 * 		0	ok
 */
int release_process_lock(void *plock)
{
	process_lock_t *lock = plock;

	if (!lock) return -1;

	fprintf(stdout, "<%s> release lock\n", __func__);
	pthread_mutex_unlock(&lock->lock);

	return 0;
}


int wait_process_cond(void *plock)
{
	process_lock_t *lock = plock;

	if (!lock) return -1;

	fprintf(stdout, "<%s> wait cond\n", __func__);
	pthread_cond_wait(&lock->cond, &lock->lock);

	return 0;
}

int signal_process_cond(void *plock)
{
	process_lock_t *lock = plock;

	if (!lock) return -1;

	fprintf(stdout, "<%s> signal cond\n", __func__);
	pthread_cond_signal(&lock->cond);

	return 0;
}

int broadcast_process_cond(void *plock)
{
	process_lock_t *lock = plock;

	if (!lock) return -1;

	fprintf(stdout, "<%s> broadcast signal\n", __func__);
	pthread_cond_broadcast(&lock->cond);

	return 0;
}




