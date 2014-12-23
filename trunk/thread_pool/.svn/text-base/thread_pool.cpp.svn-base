/*
 * file		:	thead_pool.cpp
 * description	:	implement the thread pool class 
 * date		:	2012-07-25
 * author	:	john lin
 */

#include <stdio.h>		// for fprintf and so on
#include <unistd.h>		// for usleep
#include "thread_pool.h"

/*
 * PUBLIC INTERFACES OF THREAD POOL
 */

/*
 * arguments:
 * 	init_thread_num		how many threads to create 
 * 				at the create pool time while 
 * 				calling create_thread_pool routine
 */
thread_pool::thread_pool(int init_thread_num)
{
	if (init_thread_num > MAX_THREADS_IN_POOL)
		init_thread_num = MAX_THREADS_IN_POOL;
	else if (init_thread_num < MIN_THREADS_IN_POOL)
		init_thread_num = MIN_THREADS_IN_POOL;

	exit_pool 	= false;
	init_map_size 	= init_thread_num;
	pthread_mutex_init(&p_lock, NULL);
	pthread_cond_init(&p_cond, NULL);
}

thread_pool::~thread_pool()
{
	pthread_mutex_destroy(&p_lock);
	pthread_cond_destroy(&p_cond);
}

/*
 * create the thread pool
 * arguments
 * 	sync_num	: how many threads can run con 
 * 			  (NOT USED BECAUSE THIS WILL CAUSE PROBLEM 
 * 			   WHILE THE THREAD CAN NOT GET RESOURCE AND 
 * 			   THE THTREAD WILL SLEEP WAITING WAKE UP AGAIN 
 * 			   WHICH WILL NO BODY DO THE WAKE UP JOB)
 * return value
 * 	0		success
 * 	-1		error
 */
int thread_pool::create_thread_pool(int sync_num)
{
	int	i;
	int 	ret;
	
/*
	ret = sem_init(&num_task_con, 0, sync_num);	// shared in this process' threads;
	if (0 != ret)
	{
		fprintf(stderr, "<%s:%s> unable to initialize sem: num_task_con, return value: %d\n", 
				__FILE__, __func__, ret);
		return -1;
	}
*/

	for (i = 0; i < init_map_size; i++) {
		if (create_one_thread()) {
			fprintf(stderr, "<%s:%s> create one thread error\n",
					__FILE__, __func__);
			continue;
		}
	}

	return 0;
}

/*
 * create a new pthread and add the new pthread to the pool
 * return value:
 * 	0	success
 * 	-1	error
 */
int thread_pool:: create_one_thread()
{
	pthread_worker new_worker = NULL;

	new_worker = new thread_worker;
	if (!new_worker) {
		fprintf(stderr, "<%s:%s> unable to allocate memory for new thread\n",
				__FILE__, __func__);
		return -1;
	}

	pthread_mutex_lock(&p_lock);

	if (pool_add_worker(new_worker, NULL, NULL)) {
		pthread_mutex_unlock(&p_lock);
		fprintf(stderr, "<%s:%s> unable add new worker to pool\n", 
				__FILE__, __func__);
		return -1;
	}
	pthread_cond_wait(&p_cond, &p_lock);

	pthread_mutex_unlock(&p_lock);

	return 0;
}



/*
 * p_lock p_cond protect this, should first get p_lock, 
 * after pool_add_worker return release the lock
 */
int thread_pool::pool_add_worker(pthread_worker new_worker, work_func func, void* arg)
{
	int	ret = 0;

	if (mapper.size() < init_map_size)
	{
		new_worker->is_busy 	= false;
		new_worker->tid 	= NULL;
		new_worker->arg 	= arg;
		new_worker->func 	= func;
		pthread_mutex_init(&new_worker->lock, NULL);
		pthread_cond_init(&new_worker->cond, NULL);

		ret = pthread_create(&new_worker->tid, NULL, pool_worker_thread, this);
		if (0 != ret)
		{
			fprintf(stderr, "<%s:%s> pthread_create error: %d\n",
					__FILE__, __func__, ret);
			return -1;
		}
		mapper.insert(pair<pthread_t, pthread_worker>(new_worker->tid, new_worker));
	}
	else
	{
		fprintf(stderr, "<%s:%s> pool size: %d reach init_map_size: %d\n",
				__FILE__, __func__, mapper.size(), init_map_size);
		return -1;
	}
//	fprintf(stdout, "<%s:%s> create a new thread: %ld\n", 
//			__FILE__, __func__, new_worker->tid);

	return 0;
}

/*
 * add the work to thread pool, the thread pool will
 * choose ont lazy thread do the job, if all the threads
 * in the pool are busy or no thread running in the pool
 * return -1, otherwise return 0 (success)
 *
 * arguments:
 * 		func	the work to do
 * 		arg	will pass to func
 * return value:
 * 	-1	threads in pool all are busy or zero threads in pool
 * 	0	success add the work to threads in pool
 */
int thread_pool::pool_add_work(work_func func, void* arg)
{
	pthread_worker worker;
	thread_worker_map::iterator iter;

	/*
	 * search for the unbusy pthread
	 */
	pthread_mutex_lock(&p_lock);	// get p_lock

	for (iter = mapper.begin(); iter != mapper.end(); iter++)
	{
//		fprintf(stdout, "search thread : %ld\n", iter->second->tid);
		pthread_mutex_lock(&iter->second->lock);
		if (!iter->second->is_busy)
		{
			iter->second->is_busy = true;
			pthread_mutex_unlock(&iter->second->lock);
			break;
		}
//		fprintf(stdout, "thread : %ld busy\n", iter->second->tid);
		pthread_mutex_unlock(&iter->second->lock);
	}
	if (iter == mapper.end())
	{
		fprintf(stdout, "<%s:%s> %s\n", __FILE__, __func__, 
			mapper.size() ? "pool's threads are busy" : \
				"there is no threads running in the pool");
		pthread_mutex_unlock(&p_lock);
		return -1;
	}
	else
	{
		worker = iter->second;
	}

	pthread_mutex_unlock(&p_lock);	// release p_lock

	pthread_mutex_lock(&worker->lock);
	worker->func 	= func;
	worker->arg    	= arg;
	pthread_cond_signal(&worker->cond);
	pthread_mutex_unlock(&worker->lock);
	
	return 0;
}

/*
 * create a thread do the job and wait util the job is done
 * return value
 * 	-1	error
 * 	0	success
 */
int thread_pool::add_work_wait(work_func func, void *arg)
{
	thread_worker *worker = NULL;
	
	worker = new thread_worker;
	if (!worker) return -1;

	worker->arg 	= arg;
	worker->func 	= func;
	pthread_mutex_init(&worker->lock, NULL); 
	pthread_cond_init(&worker->cond, NULL);

	pthread_mutex_lock(&worker->lock);

	if (pthread_create(&worker->tid, NULL, thread_do_work_wait, worker)) {
		fprintf(stderr, "<%s:%s> unable to create thread_do_work_wait\n",
				__FILE__, __func__);
		return -1;
	}

	pthread_cond_wait(&worker->cond, &worker->lock);
	pthread_mutex_unlock(&worker->lock);
	
	return 0;
}

/*
 * thread to do the work add by add_work_wait routine
 */
void *thread_pool::thread_do_work_wait(void *arg)
{
	thread_worker *worker = NULL;

	if (!arg) return NULL;
	worker = (thread_worker *)arg;

	pthread_mutex_lock(&worker->lock);

	if (worker->func) worker->func(worker->arg);

	pthread_cond_signal(&worker->cond);
	pthread_mutex_unlock(&worker->lock);

	return NULL;
}

/*
 * destroy the thread pool
 */
int thread_pool::destroy_thread_pool()
{
	if (exit_pool)
	{
		return -1;
	}
	exit_pool = true;
	
	pthread_mutex_lock(&p_lock);

	thread_worker_map::iterator iter;
	for (iter = mapper.begin(); iter != mapper.end(); iter++)
	{
                pthread_mutex_lock(&iter->second->lock);
                if (iter->second->is_busy) {    // give it a chance to do the work, but will drop the work too
                        fprintf(stderr, "thread %ld is busy, give it a chance to stop\n", 
					iter->second->tid);
                        pthread_cond_signal(&iter->second->cond);
                }
                pthread_mutex_unlock(&iter->second->lock);
                usleep(40);

		pthread_mutex_lock(&iter->second->lock);
		iter->second->is_busy = false;
		pthread_cond_signal(&iter->second->cond);
		pthread_mutex_unlock(&iter->second->lock);
		usleep(10);

		if (0 != iter->second->tid)
		{
//			pthread_join(iter->second->tid, NULL);
		}
		pthread_mutex_destroy(&iter->second->lock);
		pthread_cond_destroy(&iter->second->cond);
		delete iter->second;
	}
	mapper.clear();

	pthread_mutex_unlock(&p_lock);

	usleep(300);

//	sem_destroy(&num_task_con);

	return 0;
}

/*
 * do the work ( this will be called by threads running in the thread pool
 */
int thread_pool::thread_do_work()
{
	pthread_t tid = pthread_self();

	pthread_mutex_lock(&p_lock);

	pthread_worker worker = mapper[tid];

	pthread_mutex_lock(&worker->lock);		// for make sure that for the first time create this pthread, 
							// this child pthread will run before parent thread set it is status to busy
							//
	pthread_cond_signal(&p_cond);	// wake up the parent thread, that we are running	for the first time the child pthread is created 
	pthread_mutex_unlock(&p_lock);
	
	while (!exit_pool)
	{
//		fprintf(stdout, "<%s:%s> thread %ld waiting signal to do job...\n", 
//				__FILE__, __func__, pthread_self());
		pthread_cond_wait(&worker->cond, &worker->lock);

		if (worker->is_busy)
		{
	/*
			fprintf(stdout, "<%s:%s> getting resource\n", __FILE__, __func__);
			if (0 != sem_trywait(&num_task_con))		// get the resource, can we run???
			{
				worker->is_busy = false;		// reset to false maybe can solve the problem (see line 39)
				continue;
			}
	 */
			if (worker->func)
				worker->func(worker->arg);

	//		sem_post(&num_task_con);		// release the resource, we are done with the job

			worker->func	= NULL;
			worker->arg 	= NULL;
			worker->is_busy	= false;
		}
	}

	pthread_mutex_unlock(&worker->lock);

	
	return 0;
}

/*
 * the thread running in the thread pool
 */
void* thread_pool::pool_worker_thread(void *arg)
{
	thread_pool *p_this = (thread_pool *) arg;
	pthread_detach(pthread_self());
	p_this->thread_do_work();
	return NULL;
}

