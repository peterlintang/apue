
/*
 * test the mq interfaces
 */

#include <string.h>
#include "mq-shared.h"

#define MQ_NAME		"/hello.txt"
#define MQ_OPEN_FLAGS	(O_CREAT | O_NONBLOCK | O_RDWR)
#define MQ_ACCESS_MODE	(S_IRUSR | S_IWUSR)
#define	MQ_MAX_MSG	4		// mex is 10
#define MQ_MSG_SIZE	8199		// mex is 8192

void *consume_thread(void *arg)
{
	int	i;
	char	buf[256];
	int	prio;
	int	recv_len;
	mq_t *mq = (mq_t *)arg;
	if (!mq) return NULL;

//	sleep(2);
	fprintf(stdout, "pthread runing\n");
	for (i = 0; i < 10; i++) {
		memset(buf, 'c', 255);
		recv_len = mq_get(mq, buf, MQ_MSG_SIZE, &prio);
		buf[recv_len] = '\0';
		fprintf(stdout, "recv %d bytes, prio: %d\n", recv_len, prio);
		fprintf(stdout, "%d, content: %s\n", i, buf);
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	int	i;
	pthread_t tid;
	mq_t	*mq;
	char	buf[256] = "hello world";
	char	buf2[4096];
	int	prio = 4;
	int	get_len = 0;
	int	send_len = 0;

	mq = create_mq_t(MQ_NAME, MQ_OPEN_FLAGS, MQ_ACCESS_MODE, MQ_MAX_MSG, MQ_MSG_SIZE);
	if (!mq) {
		fprintf(stderr, "can not create a new mq\n");
		return -1;
	}

/*
	memset(buf2, 'b', 255);
	fprintf(stdout, "putting %d bytes, prio: %d\n", strlen(buf), prio);
	mq_put(mq, buf, strlen(buf), prio);
	fprintf(stdout, "put ok\n");

	get_len = mq_get(mq, buf2, 409600, &prio);	// the length of the buf must greater than the msg's szie
	buf2[get_len] = '\0';
	fprintf(stdout, "get %d bytes, str: %s, prio: %d\n", get_len, buf2, prio);
*/

	fprintf(stdout, "create thread\n");
	pthread_create(&tid, NULL, consume_thread, mq);
	fprintf(stdout, "OK\n");

	for (i = 0; i < 10; i++) {
		sleep(1);
		fprintf(stdout, "putting %d bytes, prio: %d\n", strlen(buf), prio);
		send_len = mq_put(mq, buf, strlen(buf), prio);
		fprintf(stdout, "put ok %d, return value: %d\n", i, send_len);
	}
	sleep(2);
	fprintf(stdout, "destroy mq \n");
	destroy_mq_t(&mq);

	return 0;
}
