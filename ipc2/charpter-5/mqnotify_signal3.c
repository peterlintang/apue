
/*
 * 利用信号处理程序接收消息队列由空变为有数据时的事件
 * 信号处理程序仅设置标志，然后线程处理
 * 使用非堵塞读，处理在for循环中当信号处理程序返回后
 * 调用mq_notify前有消息放到队列中
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mqueue.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>


static volatile sig_atomic_t mqflag = 0;

static void sig_usr1(int sig)
{

	mqflag = 1;
}

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
	sigset_t oldmask;
	sigset_t newmask;
	sigset_t zeromask;
	ssize_t n;
	char *buf;
	unsigned int prio = 0;

	if (argc != 2)
		usage(argv[0]);


	mqd = mq_open(argv[1], O_RDONLY | O_NONBLOCK);

	memset(&attr, 0, sizeof(attr));
	mq_getattr(mqd, &attr);
	buf = calloc(attr.mq_msgsize, sizeof(char));

	sigemptyset(&zeromask);
	sigemptyset(&oldmask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGUSR1);

	signal(SIGUSR1, sig_usr1);

	event.sigev_notify = SIGEV_SIGNAL;
	event.sigev_signo = SIGUSR1;
	mq_notify(mqd, &event);

	for (; ;)
	{
		sigprocmask(SIG_BLOCK, &newmask, &oldmask);
		while (mqflag == 0)
			sigsuspend(&zeromask);

		mqflag = 0;
		mq_notify(mqd, &event);

		while ((n = mq_receive(mqd, buf, attr.mq_msgsize, &prio)) > 0)
			fprintf(stdout, "thread recevied, read: %ld, bytes, prio: %u\n",
				(long)n, prio);
		if (errno != EAGAIN)
		{
			fprintf(stderr, "mq_receive failed: %s\n", strerror(errno));
			exit(1);
		}

		sigprocmask(SIG_UNBLOCK, &newmask, NULL);
	}

	free(buf);
	mq_close(mqd);

	return 0;
}




