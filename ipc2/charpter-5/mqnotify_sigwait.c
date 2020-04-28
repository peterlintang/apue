
/*
 * 仅使用sigwait等待一个信号，不用信号处理程序
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mqueue.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>




static void usage(char *proc)
{
	fprintf(stdout, "usage: %s <name>\n", proc);
	exit(0);
}



int main(int argc, char *argv[])
{
	mqd_t mqd;
	struct sigevent event;
	struct mq_attr attr;
	sigset_t newmask;
	sigset_t oldmask;
	ssize_t n;
	char *buf;
	unsigned int prio = 0;
	int signo;

	if (argc != 2)
		usage(argv[0]);


	mqd = mq_open(argv[1], O_RDONLY | O_NONBLOCK);

	memset(&attr, 0, sizeof(attr));
	mq_getattr(mqd, &attr);
	buf = calloc(attr.mq_msgsize, sizeof(char));

	sigemptyset(&oldmask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGUSR1);

	event.sigev_notify = SIGEV_SIGNAL;
	event.sigev_signo = SIGUSR1;
	mq_notify(mqd, &event);

	sigprocmask(SIG_BLOCK, &newmask, &oldmask);

	for (; ;)
	{
		sigwait(&newmask, &signo);
		if (signo == SIGUSR1)
		{
			mq_notify(mqd, &event);

			while ((n = mq_receive(mqd, buf, attr.mq_msgsize, &prio)) > 0)
				fprintf(stdout, "thread recevied, read: %ld, bytes, prio: %u\n",
					(long)n, prio);
			if (errno != EAGAIN)
			{
				fprintf(stderr, "mq_receive failed: %s\n", strerror(errno));
				exit(1);
			}
		}


	}

	free(buf);
	mq_close(mqd);

	return 0;
}




