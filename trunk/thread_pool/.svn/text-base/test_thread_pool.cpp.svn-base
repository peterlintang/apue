/*
 * this is for test the class CThreadPool
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	// for sleep

#include "thread_pool.h"
#pragma GCC dependency "test_thread.sh"	oh on	// for test #pragma 

int do_job(void *arg)
{
	static int	i = 0;
	fprintf(stdout, "<%s:%s> hello we are doing %d job\n", 
			__FILE__, __func__, i++);
	sleep(1);
	return 0;
}

int main(int argc, char *argv[])
{
	int	i;

	thread_pool *pool = new thread_pool(8);
	if (pool && pool->create_thread_pool(1)) {
		fprintf(stderr, "unable to start thread pool\n");
		delete pool;
		pool = NULL;
	}

	fprintf(stdout, "add 1 work\n\n");
	if (pool && pool->pool_add_work(do_job, NULL)) {
		fprintf(stderr, "unable to add work\n");
		pool->destroy_thread_pool();
		delete pool;
		pool = NULL;
	}
	fprintf(stdout, "add 2 work\n\n");
	if (pool && pool->pool_add_work(do_job, NULL)) {
		fprintf(stderr, "unable to add work\n");
		pool->add_work_wait(do_job, NULL);
//		pool->destroy_thread_pool();
//		delete pool;
//		pool = NULL;
	}

	fprintf(stdout, "add 3 work\n\n");
	if (pool && pool->pool_add_work(do_job, NULL)) {
		fprintf(stderr, "unable to add work\n");
		pool->add_work_wait(do_job, NULL);
		//pool->destroy_thread_pool();
//		delete pool;
//		pool = NULL;
	}

	for (i = 0; i < 40; i++) {
		fprintf(stdout, "add %d work\n\n", i);
		if (pool && pool->pool_add_work(do_job, NULL)) {
			fprintf(stderr, "unable to add work\n");
			pool->add_work_wait(do_job, NULL);
			//pool->destroy_thread_pool();
//			delete pool;
//			pool = NULL;
		}
	}

	fprintf(stdout, "add 4 work\n\n");
	if (pool)
		pool->add_work_wait(do_job, NULL);
//	sleep(4);	// wait for job done

	if (pool) {
		pool->destroy_thread_pool();
		delete pool;
		pool = NULL;
	}

	return 0;
}
