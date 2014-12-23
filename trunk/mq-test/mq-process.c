
/*
 * implements the interfaces of mq
 * just used this interfaces in threads in the same process
 * we just not support process now,
 * filename:	mq-shared.c
 */

#include <string.h>
#include "mq-process.h"

int create_mq_process_t(const char *name, long maxmsg, long msgsize, int block)
{
	int	flags = 0;
	mode_t	mode;
	mqd_t	fd;
	struct mq_attr attr;

	if (!name) return -2;


	if (block)
		attr.mq_flags 	= 0;
	else
		attr.mq_flags 	= O_NONBLOCK;

	attr.mq_maxmsg 	= maxmsg > JOHN_MQ_PROCESS_MAX_MSG ? \
				JOHN_MQ_PROCESS_MAX_MSG : maxmsg;
	attr.mq_msgsize = msgsize > JOHN_MQ_PROCESS_MAX_MSG_SIZE ? \
				JOHN_MQ_PROCESS_MAX_MSG_SIZE : msgsize;
	attr.mq_curmsgs = 0;

	fprintf(stdout, "set attr\n");
	fprintf(stdout, " mq_flags: %ld mq_maxmsg: %ld\n", 
			attr.mq_flags, attr.mq_maxmsg);
	fprintf(stdout, "mq_msgsize: %ld mq_curmsgs: %ld\n", 
			attr.mq_msgsize, attr.mq_curmsgs);

	flags = (O_CREAT | O_EXCL | O_RDWR);
	mode  = (S_IRUSR | S_IWUSR);
	if ((fd = mq_open(name, flags, mode, &attr)) == -1) {
		perror("mq_open");
		return -1;
	}

	if(!mq_getattr(fd, &attr)) {
		fprintf(stdout, "get attr\n");
		fprintf(stdout, " mq_flags: %ld mq_maxmsg: %ld\n", 
				attr.mq_flags, attr.mq_maxmsg);
		fprintf(stdout, "mq_msgsize: %ld mq_curmsgs: %ld\n", 
				attr.mq_msgsize, attr.mq_curmsgs);
	}

	if (mq_close(fd)) {
		perror("mq_close");
		return -1;
	}

	fprintf(stdout, "create mq : %s ok\n", name);
	return 0;
}

int destroy_mq_process_t(const char *pathname)
{
	if (!pathname) {
		fprintf(stderr, "arguments error\n");
		return -2;
	}

	if(mq_unlink(pathname)) {
		perror("mq_unlik");
		return -1;
	}

	return 0;
}

/*
 * open an exist mq
 * @pathname	:	id for mq
 * @mode	:	S_IRUSR S_WUSR ....
 */
mq_process_t *open_mq_process(const char *pathname, int flags)
{
	mq_process_t *mq = NULL;

	if (!pathname) {
		fprintf(stderr, "arguemnts error\n");
		return NULL;
	}

	if (!(mq = calloc(1, sizeof(*mq)))) {
		perror("calloc 1");
		return NULL;
	}

	if (!(mq->name = strdup(pathname))) {
		perror("calloc 2");
		free(mq);
		return NULL;
	}

	if ((mq->fd = mq_open(mq->name, flags)) == -1) {
		perror("mq_open");
		free(mq->name);
		free(mq);
		return NULL;
	}

	fprintf(stdout, "open mq, path: %s, fd: %d\n", mq->name, mq->fd);

	return mq;
}

void close_mq_process_t(mq_process_t **ppmq)
{
	mq_process_t *mq = NULL;

	if (ppmq && *ppmq) {
		mq = *ppmq;
		fprintf(stdout, "close mq, path: %s, fd: %d\n", 
				mq->name, mq->fd);
		if (mq_close(mq->fd))
			perror("mq_close");
		free(mq->name);
		free(mq);
	}
}

/*
 * put a message into mq
 * @mq
 * @buf		message stored in the @buf
 * @len		how many bytes in @buf will put th mq
 * @prio	the prio of message
 */
int mq_process_t_put(mq_process_t *mq, char *buf, int len, unsigned int prio)
{
	int	total = 0;

	if (!mq || !buf || len < 0) {
		fprintf(stderr, "mq: %p, buf: %p, len: %d\n", mq, buf, len);
		return -2;
	}

	total = mq_send(mq->fd, buf, len, prio);
	if (total == -1) {
		perror("mq_send");
	}

	fprintf(stdout, "send total %d\n", total);
	return total;
}


/*
 * get a message from the mq
 * @mq
 * @buf		for store message
 * @len		the length of the buf, must greater than mq's size
 * @prio	prio of ms
 */
int mq_process_t_get(mq_process_t *mq, char *buf, int len, unsigned int *prio)
{
	int	recv;

	if (!mq || !buf || len < 0) {
		fprintf(stderr, "arguments error, mq: %p, buf: %p, len: %d\n",
				mq, buf, len);
		return -2;
	}

	fprintf(stdout, "receving msg\n");
	recv = mq_receive(mq->fd, buf, len, prio);
	if (recv == -1) {
		perror("mq_receive");
	}

	fprintf(stdout, "recv %d bytes\n", recv);

	return recv;
}

