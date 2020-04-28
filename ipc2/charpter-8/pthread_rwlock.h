
/*
 * 用互斥锁与条件变量实现读写锁
 *
 */
#ifndef __MY_PTHREAD_RWLOCK_H
#define __MY_PTHREAD_RWLOCK_H

#include <pthread.h>

typedef struct {
	pthread_mutex_t rw_mutex;
	pthread_cond_t rw_condreaders;
	pthread_cond_t rw_condwriters;
	int rw_magic;
	int rw_nwaitreaders;
	int rw_nwaitwriters;
	int rw_refcount;	/* -1:写入锁，0：可用；> 0，读取锁 */
} Pthread_rwlock_t;

#define RW_MAGIC	0x19283746

#define PTHREAD_RWLOCK_INITIALZER { \
		PTHREAD_MUTEX_INITIALIZER,	\
		PTHREAD_COND_INITIALIZER,	\
		PTHREAD_COND_INITIALIZER,	\
		RW_MAGIC,					\
		0, 0, 0 }

typedef int Pthread_rwlockattr_t;		// dummy , dont support, 

int Pthread_rwlock_destroy(Pthread_rwlock_t *);
int Pthread_rwlock_init(Pthread_rwlock_t *, Pthread_rwlockattr_t *);
int Pthread_rwlock_rdlock(Pthread_rwlock_t *);
int Pthread_rwlock_tryrdlock(Pthread_rwlock_t *);
int Pthread_rwlock_wrlock(Pthread_rwlock_t *);
int Pthread_rwlock_trywrlock(Pthread_rwlock_t *);
int Pthread_rwlock_unlock(Pthread_rwlock_t *);

#endif // end of __MY_PTHREAD_RWLOCK_H



