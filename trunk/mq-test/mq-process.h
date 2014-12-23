
/*
 * implement the interfaces of mq
 * just used this interfaces in threads, 
 * we now want to implement process support
 *
 * posix ipc
 *
 * filename:	mq-process.h
 */

#ifndef JOHN_LIN_MQ_PROCESS_H__
#define JOHN_LIN_MQ_PROCESS_H__

#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

#define JOHN_MQ_PROCESS_MAX_MSG		10
#define JOHN_MQ_PROCESS_MAX_MSG_SIZE 	8192

typedef struct __mq_process_t {
//	int			msgs;
//	int			maxmsg;
	mqd_t			fd;
	char			*name;
} mq_process_t;

int create_mq_process_t(const char *pathname, long maxmsg, 
			long msgsize, int block);
int destroy_mq_process_t(const char *pathname);
mq_process_t *open_mq_process_t(const char *pathname, mode_t mode);
void close_mq_process_t(mq_process_t **mqp);
int mq_process_t_put(mq_process_t *mqp, char *buf, int len, unsigned int prio);
int mq_process_t_get(mq_process_t *mqp, char *buf, int len, unsigned int *prio);


#endif // JOHN_LIN_MQ_PROCESS_H__
