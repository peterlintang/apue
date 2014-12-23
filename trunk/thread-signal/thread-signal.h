
/*
 * implement the signals in threads env process
 * only one pthread deal with signals, other 
 * pthreads block signals, and do their own jobs
 */

#ifndef JOHN_LIN_THREAD_SIGNALS_H__
#define JOHN_LIN_THREAD_SIGNALS_H__


#include <pthread.h>
#include <signal.h>

#define MAX_SIGNALS	32

int thread_block_signals(sigset_t *newset, sigset_t *oldset);
int thread_unblock_signals(sigset_t *newset, sigset_t *oldset);
int thread_send_signal(int signo, pthread_t tid);

#endif // JOHN_LIN_THREAD_SIGNALS_H__
