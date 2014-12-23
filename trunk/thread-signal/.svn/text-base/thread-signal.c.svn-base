
/*
 * implements the threads signal interfaces
 *
 *
 */
#include <stdio.h>
#include "thread-signal.h"

int thread_block_signals(sigset_t *newset, sigset_t *oldset)
{
	int	i;
	int	ret = 0;

	sigemptyset(newset);

	for (i = 1; i < MAX_SIGNALS; i++)
		sigaddset(newset, i);

	ret = pthread_sigmask(SIG_BLOCK, newset, oldset);
	if (ret) {
		fprintf(stderr, "<%s> set thread : %ld signal mask failed\n",
				__func__, pthread_self());
		return -1;
	}

	return 0;
}

int thread_unblock_signals(sigset_t *newset, sigset_t *oldset)
{
	int	ret = 0;

	ret = pthread_sigmask(SIG_UNBLOCK, newset, oldset);
	if (ret) {
		fprintf(stderr, "<%s> set thread : %ld signal mask failed\n",
				__func__, pthread_self());
		return -1;
	}

	return 0;
}

/*
 * send signal @signo to @tid
 */
int thread_send_signal(int signo, pthread_t tid)
{
	if (signo > 0 && signo < MAX_SIGNALS)
		return pthread_kill(tid, signo);

	return -2;
}



