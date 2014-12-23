
#include <stdio.h>
#include <stdlib.h>     /* for exit */
#include <mqueue.h>     /* for mqd_t & mq_open mq_close */
#include <sys/stat.h>   /* for S_IRUSR S_IWUSR */
#include <fcntl.h>      /* for O_xxx */
#include <unistd.h>     /* for getopt */

#define FILE_MODE S_IRUSR | S_IWUSR

int main(int argc, char **argv)
{
	mqd_t		mqd;
	struct mq_attr	attr;

	if (argc != 2) {
		fprintf(stdout, "<%s> usage: mqgetattr <name>\n", __func__);
		exit(1);
	}

	mqd = mq_open(argv[1], O_RDONLY);
	if (mqd == -1) {
		perror("mq_open");
		exit(2);
	}

	mq_getattr(mqd, &attr);
	fprintf(stdout, "<%s> max #msgs = %ld, max #bytes/msg = %ld	\
			 #currently on queue = %ld\n", __func__, 
			attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);

	mq_close(mqd);

	return 0;
}
