
/*
 * 利用信号处理程序接收消息队列由空变为有数据时的事件
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mqueue.h>
#include <unistd.h>
#include <signal.h>


static mqd_t mqd;
static struct sigevent event;
static struct mq_attr attr;

static void sig_usr1(int sig)
{
	ssize_t n;
	char *buf;
	unsigned int prio = 0;

	mq_notify(mqd, &event);

	buf = calloc(attr.mq_msgsize, sizeof(char));
	n = mq_receive(mqd, buf, attr.mq_msgsize, &prio);

	fprintf(stdout, "sigusr1 recevied, read: %ld, bytes, prio: %u\n",
				(long)n, prio);
	free(buf);

}

static void usage(char *proc)
{
	fprintf(stdout, "usage: %s <name>\n", proc);
	exit(0);
}



int main(int argc, char *argv[])
{

	if (argc != 2)
		usage(argv[0]);

	signal(SIGUSR1, sig_usr1);

	mqd = mq_open(argv[1], O_RDONLY);

	memset(&attr, 0, sizeof(attr));
	mq_getattr(mqd, &attr);

	event.sigev_notify = SIGEV_SIGNAL;
	event.sigev_signo = SIGUSR1;

	mq_notify(mqd, &event);

	for (; ;)
		pause();

	mq_close(mqd);

	return 0;
}




