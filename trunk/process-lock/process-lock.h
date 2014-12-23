/************************************************************
 * file            :       process-lock.c
 * author          :       john lin
 * date            :       Wed Aug 15 20:32:49 PDT 2012
 * desc            :       implement the interfaces of 
 *                         processes shared memory lock
 *                         and condition
 *
 * copyright (c) john lin
 **************************************************************/

/*
 * implements the pthread lock in multiple processes
 * system v ipc
 * filename:	process-lock.h
 *
 */

#ifndef JOHN_LIN_PROCESS_LOCK_H__
#define JOHN_LIN_PROCESS_LOCK_H__

#include <sys/types.h>
#include <sys/shm.h>
#include <pthread.h>
#include <errno.h>

#define PROCESS_LOCK_NAME_LEN	256

typedef struct __process_lock_t {
//	char	name[PROCESS_LOCK_NAME_LEN];
//	int	id;
//	int	status;		// 0 means can use, 1 means remove. not used now
	int	count;
	int	shmid;
//	void	*lockp;
	pthread_mutex_t	lock;
	pthread_cond_t	cond;
} process_lock_t;

void *create_process_lock(const char *pathname, int id);
int destroy_process_lock(void **pshmaddr);
void *map_process_lock(const char *pathname, int id);
int unmap_process_lock(void **plock);
int get_process_lock(void *plock);
int release_process_lock(void *plock);
int broadcast_process_cond(void *plock);
int signal_process_cond(void *plock);
int wait_process_cond(void *plock);

#endif // JOHN_LIN_PROCESS_LOCK_H__
