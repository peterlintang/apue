
/*
 * interface to create a shared memory
 * need to reconsider the interface for processes access, 
 * this now is not processes shared
 *
 * now, i think this is processes access ok, see create routine
 */

/*
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
*/

#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>
#include <errno.h>

#include "share-mem.h"


/*
 * create memory shared between processes
 * label	0	not created
 * 		1	created, just open
 */
void *create_shared_mem(const char *pathname, int id, 
				int size, int shmflg,
				const void *shmaddr, int flags)
{
	key_t		key;
	int		label = 0;
	int		shmid;
	void		*ptr = NULL;
	shared_mem_t	*shm = NULL;
	pthread_mutexattr_t attr;

	if (!pathname) return NULL;

	if ((key = ftok(pathname, id)) == -1) {
		perror("ftok");
		return NULL;
	}

	/*
	 * first check the shared memory exist or not,
	 * if the shared mem exist, just open 
	 * it with read & write permission
	 */
	shmflg |= (IPC_CREAT | IPC_EXCL);
	if (((shmid = shmget(key, size + sizeof(shared_mem_t), // create and open should detach
			shmflg)) == -1) && errno == EEXIST) {
		fprintf(stdout, "shared memory exist, just open it\n");
		if ((shmid = shmget(key, size + sizeof(shared_mem_t), 
					SHM_R | SHM_W)) == -1) {
			fprintf(stderr, "can not open shared memory, key: %d\n", key);
			return NULL;
		}
		label = 1;	// alread exist
	}

	if ((ptr = shmat(shmid, shmaddr, flags)) == (void *)-1) {
		fprintf(stderr, "unable to get the address of shared memory\n");
		perror("shmat");
		shmctl(shmid, IPC_RMID, 0);
		return NULL;
	}

	shm = (shared_mem_t *)ptr;
	if (label) goto out;

	fprintf(stdout, "create the shared memory\n");

	shm->size	= size;
	shm->key	= key;
	shm->shmid	= shmid;
	shm->read_cur	= 0;
	shm->write_cur	= 0;
	shm->open_count	= 0;
	pthread_mutexattr_init(&attr); 
	pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
	pthread_mutex_init(&shm->lock, &attr);
	pthread_mutexattr_destroy(&attr);

out:
	shm->open_count++;
	fprintf(stdout, "shared memory id: %d, open count: %d\n", 
			shmid, shm->open_count);
	return ptr;
}

void destroy_shared_mem(void **shmpp)
{
	shared_mem_t *shm = NULL; 
	fprintf(stdout, "destroying shared memory: %p\n", shmpp);
	if (shmpp && *shmpp) {
		shm = *shmpp;
		shm->open_count--;
		fprintf(stdout, "id: %d, open count: %d\n", shm->shmid, shm->open_count);
		if (!shm->open_count) pthread_mutex_destroy(&shm->lock);
		shmctl(shm->shmid, IPC_RMID, 0);
		shmdt(shm);
		fprintf(stdout, "OK\n");
		*shmpp = NULL;
	}
}

/*
void *address_at(const void *shmaddr, int flags)
{
	void 		*ptr = NULL;
	shared_mem_t 	*shm = shmaddr;

	if ((ptr = shmat(shm->shmid, shmaddr, flags)) == (void *)-1) {
		fprintf(stderr, "unable to get the address of shared memory\n");
		perror("shmat");
		return NULL;
	}

	return ptr;
}

int address_dt(void *shmaddr)
{
	shmdt(shmaddr);
	return 0;
}
*/

int read_shared_mem(void *ptr, char *buf, int len)
{
	shared_mem_t *shm = ptr;
	if (!shm || !buf || len < 0) {
		//dfprintf(stdout, "<%s> arguments error\n", __func__);
		return -1;
	}

	fprintf(stdout, "get release\n");
	pthread_mutex_lock(&shm->lock);

	if (shm->read_cur < shm->write_cur) {
		len = ((shm->read_cur + len) > shm->write_cur) ? (shm->write_cur - shm->read_cur) : len;
	} else if (shm->read_cur > shm->write_cur) {
		len = shm->size - shm->read_cur;
	} else {
		//dfprintf(stdout, "<%s> empty buf\n", __func__);
		return 0;
	}

	fprintf(stdout, "read cur: %d, write cur: %d, read bytes: %d\n", 
			shm->read_cur, shm->write_cur, len);

	memcpy(buf, ptr + (sizeof(shared_mem_t) + shm->read_cur), len);

	shm->read_cur += len;
	if (shm->read_cur == shm->size -1)
		shm->read_cur = 0;

	pthread_mutex_unlock(&shm->lock);
	fprintf(stdout, "release lock\n");

	fprintf(stdout, "read %d bytes\n", len);
	return len;
}

int write_shared_mem(void *ptr, char *buf, int len)
{
	shared_mem_t *shm = ptr;
	if (!shm || !buf || len < 0) {
		return -1;
	}

	fprintf(stdout, "get release\n");
	pthread_mutex_lock(&shm->lock);

	if (shm->read_cur < shm->write_cur)
		len = (len < shm->size - shm->write_cur) ? len : (shm->size - shm->write_cur);
	else if (shm->write_cur + 1 == shm->read_cur) {
		fprintf(stdout, "buf is full\n");
		return -2;
	} else if (shm->read_cur == shm->write_cur)
		len = len > (shm->size - shm->write_cur) ? (shm->size - shm->write_cur) : len;
	else
		len = shm->read_cur - shm->write_cur - 1;

	fprintf(stdout, "read cur: %d, write cur: %d, write bytes: %d\n", 
			shm->read_cur, shm->write_cur, len);

	memcpy(ptr + (sizeof(shared_mem_t) + shm->write_cur), buf, len);

	shm->write_cur += len;
	if (shm->write_cur == shm->size -1)
		shm->write_cur = 0;

	pthread_mutex_unlock(&shm->lock);
	fprintf(stdout, "release lock\n");

	fprintf(stdout, "write %d bytes\n", len);
	return len;
}



