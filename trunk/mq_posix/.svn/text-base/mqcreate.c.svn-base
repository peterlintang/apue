
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
	struct mq_attr attr;

	flags = O_RDWR | O_CREAT;

	while ((c = getopt(argc, argv, "em:z:")) != -1) {
		switch (c) {
		case 'e':
			flags |= O_EXCL;
			break;
		case 'm':
			attr.mq_maxmsg = atoi(optarg);
			break;
		case 'z':
			attr.mq_msgsize = atoi(optarg);
			break;
		default:
			break;
		}
	}

	if (optind != argc - 1) {
		fprintf(stdout, "<%s> usage: \
				mqcreate [ -e ] [ -m maxmsg -z msgsize ] <name>\n", 
				__func__);
		exit(1);
	}

	mqd = mq_open(argv[optind], flags, FILE_MODE, 
				(attr.mq_maxmsg != 0) ? &attr : NULL);
	if (mqd == -1) {
		perror("mq_open");
		exit(2);
	}

	return 0;
}
