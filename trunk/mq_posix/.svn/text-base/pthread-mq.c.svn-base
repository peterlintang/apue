
#include <stdio.h>
#include <stdlib.h>     /* for exit */
#include <mqueue.h>     /* for mqd_t & mq_open mq_close */
#include <sys/stat.h>   /* for S_IRUSR S_IWUSR */
#include <fcntl.h>      /* for O_xxx */
#include <unistd.h>     /* for getopt */
#include <signal.h>     /* for SIGUSRx */
#include <errno.h>      /* for errno */

#define FILE_MODE S_IRUSR | S_IWUSR

mqd_t	mqd;
struct mq_attr 	attr;
struct sigevent	sigev;

static void notify_thread(union sigval);

int main(int argc, char **argv)
{
	int	count = 0;

	if (argc != 2) {
		fprintf(stdout, "<%s> usage: pthread-mq <name>\n", __func__);
		exit(1);
	}

	mqd = mq_open(argv[1], O_RDONLY | O_NONBLOCK);
	if (mqd == -1) {
		perror("mq_open");
		exit(2);
	}

	mq_getattr(mqd, &attr);

	sigev.sigev_notify = SIGEV_THREAD;
	sigev.sigev_value.sival_ptr = NULL;
	sigev.sigev_notify_function = notify_thread;
	sigev.sigev_notify_attributes = NULL;

	mq_notify(mqd, &sigev);
	
	for (; ; ) {
		pause();
		fprintf(stdout, "<%s> wake up %d\n", __func__, count++);
	}

	exit(0);
}

static void notify_thread(union sigval arg)
{
	ssize_t	n;
	void *buff;

	fprintf(stdout, "<%s> notify_thread start\n", __func__);
	buff = malloc(attr.mq_msgsize);
	mq_notify(mqd, &sigev);

	while ((n = mq_receive(mqd, buff, attr.mq_msgsize, NULL)) >= 0) {
		fprintf(stdout, "<%s> read %d bytes\n", __func__, n);
	}

	free(buff);

	if (errno != EAGAIN) {
		perror("mq_receive");
		exit(4);
	}

	pthread_exit(NULL);
}
