
/*
 * implements the shared memory interfaces
 * for processes access
 *
 * system v ipc
 *
 * filename:	shared-mem.h
 */

#ifndef JOHN_LIN_SHARED_MEM_H__
#define JOHN_LIN_SHARED_MEM_H__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//

#define dfprintf(out, fmt, args, ...) fprintf(out, fmt, ##args)

/*
#ifdef _DEBUG_SHARED_MEM
# define dfprintf(out, fmt, args, ...)
#else
# define dfprintf(out, fmt, args, ...)
#endif
*/

typedef struct shared_mem {
	int	open_count;
	int	size;
	int	read_cur;
	int	write_cur;
	key_t	key;
	int	shmid;
	pthread_mutex_t lock;
//	pthread_cond_t	cond;
} shared_mem_t;

void *create_shared_mem(const char *pathname, int id,
				int size, int flag,
				const void *shmaddr, int flag2);
void destroy_shared_mem(void **shmpp);

/*
void *address_at(const void *shmaddr, int flags);
int address_dt(void *shmaddr);
*/


int read_shared_mem(void *shm, char *buf, int len);

int write_shared_mem(void *shm, char *buf, int len);

#endif 	// JOHN_LIN_SHARED_MEM_H__
