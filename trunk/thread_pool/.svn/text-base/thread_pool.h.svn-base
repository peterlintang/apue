/*
 * CThreadPool.h
 *
 *  Created on: 2012-5-14
 *      Author: Administrator
 */

#ifndef JOHN_LIN_THREAD_POOL_H_
#define JOHN_LIN_THREAD_POOL_H_

#include <pthread.h>		// for pthread_mutex_t pthread_cond_t pthread_func_XXX
#include <semaphore.h>		// for semaphore

#include <map>

#define MIN_THREADS_IN_POOL		2					// 池中同时运行的最少线程数
#define MAX_THREADS_IN_POOL		16		// 池中同时运行的最多线程数

using namespace std;

typedef int (*work_func)(void* arg);

typedef struct tag_thread_worker
{
	bool is_busy;
	pthread_t tid;
	void *arg;
	work_func func;
	pthread_mutex_t lock;		// protect this struct
	pthread_cond_t cond;
} thread_worker, *pthread_worker;

typedef map<pthread_t, pthread_worker> thread_worker_map;

class thread_pool
{
public:
	thread_pool(int init_thread_num);
	~thread_pool();
public:
	int create_thread_pool(int sync_num);
	int destroy_thread_pool();
	int pool_add_work(work_func func, void* arg);
	int add_work_wait(work_func func, void *arg);
	
private:
	int create_one_thread();
	int pool_add_worker(pthread_worker new_worker,  work_func func, void* arg);
	int thread_do_work();
	
	static void *thread_do_work_wait(void *arg);
	static void* pool_worker_thread(void *arg);

private:
	bool 			exit_pool;		// mark for exit
	int  			init_map_size;		// how many pthread can create on the StartTreadPool routine
//	sem_t 			num_task_con;		// to indicate how many pthreads can run simultaneously ( not used, see XX.cpp)
	pthread_mutex_t 	p_lock;		// to protect m_threadWorkMap
	pthread_cond_t		p_cond;
	thread_worker_map 	mapper;	// store pthread created, can find by tid;
};

#endif /* THREAD_POOL_H_ */
