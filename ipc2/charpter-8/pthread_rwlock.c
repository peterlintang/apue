
/*
 * 用互斥锁与条件变量实现读写锁
 *
 */

#include <stdio.h>
#include <errno.h>

#include "pthread_rwlock.h"

static void rwlock_cancelrdwait(void *arg)
{
	Pthread_rwlock_t *rw = (Pthread_rwlock_t *)arg;

	rw->rw_nwaitreaders--;
	pthread_mutex_unlock(&rw->rw_mutex);
}

static void rwlock_cancelwrwait(void *arg)
{
	Pthread_rwlock_t *rw = (Pthread_rwlock_t *)arg;

	rw->rw_nwaitwriters--;
	pthread_mutex_unlock(&rw->rw_mutex);
}

int Pthread_rwlock_destroy(Pthread_rwlock_t *rw)
{
	if (rw->rw_magic != RW_MAGIC)
		return (EINVAL);

	if (rw->rw_refcount != 0 || rw->rw_nwaitreaders != 0 || rw->rw_nwaitwriters != 0)
		return (EBUSY);

	pthread_mutex_destroy(&rw->rw_mutex);
	pthread_cond_destroy(&rw->rw_condreaders);
	pthread_cond_destroy(&rw->rw_condwriters);
	rw->rw_magic = 0;

	return 0;
}

int Pthread_rwlock_init(Pthread_rwlock_t *rw, Pthread_rwlockattr_t *attr)
{
	int result = 0;

	if (attr != NULL)
		return (EINVAL);

	if ((result = pthread_mutex_init(&rw->rw_mutex, NULL)) != 0)
		goto err1;

	if ((result = pthread_cond_init(&rw->rw_condreaders, NULL)) != 0)
		goto err2;

	if ((result = pthread_cond_init(&rw->rw_condwriters, NULL)) != 0)
		goto err3;

	rw->rw_nwaitreaders = 0;
	rw->rw_nwaitwriters = 0;
	rw->rw_refcount = 0;
	rw->rw_magic = RW_MAGIC;

	return 0;

err3:
	pthread_cond_destroy(&rw->rw_condreaders);
err2:
	pthread_mutex_destroy(&rw->rw_mutex);
err1:
	return result;
}

int Pthread_rwlock_rdlock(Pthread_rwlock_t *rw)
{
	int result = 0;

	if (rw == NULL || rw->rw_magic == RW_MAGIC)
		return (EINVAL);

	if ((result = pthread_mutex_lock(&rw->rw_mutex)) != 0)
		return (result);

	/*写锁优先*/
	while (rw->rw_refcount < 0 || rw->rw_nwaitwriters > 0)
	{
		rw->rw_nwaitreaders++;
		pthread_cleanup_push(rwlock_cancelrdwait, (void *)rw);
		result = pthread_cond_wait(&rw->rw_condreaders, &rw->rw_mutex);
		pthread_cleanup_pop(0);
		rw->rw_nwaitreaders--;
		if (result != 0)
			break;
	}

	if (result == 0)
		rw->rw_refcount++;

	pthread_mutex_unlock(&rw->rw_mutex);
	return result;
}

int Pthread_rwlock_tryrdlock(Pthread_rwlock_t *rw)
{
	int result = 0;

	if (rw == NULL || rw->rw_magic == RW_MAGIC)
		return (EINVAL);

	if ((result = pthread_mutex_lock(&rw->rw_mutex)) != 0)
		return (result);

	if (rw->rw_refcount < 0 || rw->rw_nwaitwriters > 0)
	{
		result = EBUSY;
	}
	else
	{
		rw->rw_refcount++;
	}

	pthread_mutex_unlock(&rw->rw_mutex);
	return result;
}

int Pthread_rwlock_wrlock(Pthread_rwlock_t *rw)
{
	int result = 0;

	if (rw == NULL || rw->rw_magic == RW_MAGIC)
		return (EINVAL);

	if ((result = pthread_mutex_lock(&rw->rw_mutex)) != 0)
		return (result);

	while (rw->rw_refcount != 0 )
	{
		rw->rw_nwaitwriters++;
		pthread_cleanup_push(rwlock_cancelwrwait, (void *)rw);
		result = pthread_cond_wait(&rw->rw_condwriters, &rw->rw_mutex);
		pthread_cleanup_pop(0);
		rw->rw_nwaitwriters--;
		if (result != 0)
			break;
	}

	if (result == 0)
		rw->rw_refcount = -1;

	pthread_mutex_unlock(&rw->rw_mutex);
	return result;
}

int Pthread_rwlock_trywrlock(Pthread_rwlock_t *rw)
{
	int result = 0;

	if (rw == NULL || rw->rw_magic == RW_MAGIC)
		return (EINVAL);

	if ((result = pthread_mutex_lock(&rw->rw_mutex)) != 0)
		return (result);

	if (rw->rw_refcount == 0)
		rw->rw_refcount = -1;
	else
		result = EBUSY;

	pthread_mutex_unlock(&rw->rw_mutex);
	return result;
}


int Pthread_rwlock_unlock(Pthread_rwlock_t *rw)
{
	int result = 0;

	if (rw == NULL || rw->rw_magic == RW_MAGIC)
		return (EINVAL);

	if ((result = pthread_mutex_lock(&rw->rw_mutex)) != 0)
		return (result);

	if (rw->rw_refcount > 0)	// writer has the lock
		rw->rw_refcount--;
	else if (rw->rw_refcount == -1)
		rw->rw_refcount = 0;
	else
		result = EINVAL;

	if (rw->rw_nwaitwriters > 0)
	{
		if (rw->rw_refcount == 0)
		{
			pthread_cond_signal(&rw->rw_condwriters);
		}
	}
	else if (rw->rw_nwaitreaders > 0)
	{
		pthread_cond_signal(&rw->rw_condreaders);
	}

	pthread_mutex_unlock(&rw->rw_mutex);
	return result;
}




