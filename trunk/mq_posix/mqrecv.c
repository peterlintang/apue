
#include <stdio.h>
#include <stdlib.h>     /* for exit */
#include <mqueue.h>     /* for mqd_t & mq_open mq_close */
#include <sys/stat.h>   /* for S_IRUSR S_IWUSR */
#include <fcntl.h>      /* for O_xxx */
#include <unistd.h>     /* for getopt */

#define FILE_MODE S_IRUSR | S_IWUSR


int main(int argc, char **argv)
{
	int	c;
	int	flags;
	mqd_t	mqd;
	void 	*buff;
	unsigned int prio;
	struct mq_attr	attr;

	flags = O_RDONLY;
	while ((c = getopt(argc, argv, "n")) != -1) {
		switch (c) {
		case 'n':
			flags |= O_NONBLOCK;
			break;
		default:
			break;
		}
	}

	if (optind != argc - 1) {
		fprintf(stdout, "<%s> usgae: mqrecv [ -n ] <name>\n", __func__);
		exit(1);
	}

	if ((mqd = mq_open(argv[optind], flags)) == -1) {
		perror("mq_open");
		exit(2);
	}

	mq_getattr(mqd, &attr);
	buff = malloc(attr.mq_msgsize);

	c = mq_receive(mqd, buff, attr.mq_msgsize, &prio);
	fprintf(stdout, "<%s> read %ld bytes, priority == %u\n", __func__, (long)c, prio);

	return 0;
}
