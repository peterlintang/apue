
/*
 * 使用线程接收
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mqueue.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <pthread.h>

static mqd_t mqd;
static struct sigevent event;
static struct mq_attr attr;


static void usage(char *proc)
{
	fprintf(stdout, "usage: %s <name>\n", proc);
	exit(0);
}

static void notify_thread(union sigval arg)
{
	ssize_t n;
	unsigned int prio;
	char *buf;

	mq_notify(mqd, &event);
	
	buf = calloc(attr.mq_msgsize, sizeof(char));

	while ((n = mq_receive(mqd, buf, attr.mq_msgsize, &prio)) > 0)
		fprintf(stdout, "thread(%ld) recevied, read: %ld, bytes, prio: %u\n",
			(long)pthread_self(), (long)n, prio);
	if (errno != EAGAIN)
	{
		fprintf(stderr, "mq_receive failed: %s\n", strerror(errno));
		exit(1);
	}

	free(buf);
	fprintf(stdout, "exit\n");

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{

	if (argc != 2)
		usage(argv[0]);


	mqd = mq_open(argv[1], O_RDONLY | O_NONBLOCK);

	memset(&attr, 0, sizeof(attr));
	mq_getattr(mqd, &attr);

	event.sigev_notify = SIGEV_THREAD;
	event.sigev_value.sival_ptr = NULL;
	event.sigev_notify_function = notify_thread;
	event.sigev_notify_attributes = NULL;

	mq_notify(mqd, &event);

	for ( ; ; )
		pause();

	mq_close(mqd);

	return 0;
}




