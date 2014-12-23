
#include <stdio.h>
#include <stdlib.h>	/* for exit */
#include <mqueue.h>	/* for mqd_t & mq_open mq_close */
#include <sys/stat.h>	/* for S_IRUSR S_IWUSR */
#include <fcntl.h>	/* for O_xxx */
#include <unistd.h>	/* for getopt */

#define FILE_MODE S_IRUSR | S_IWUSR

int main(int argc, char **argv)
{
	int	c;
	int	flags;
	mqd_t	mqd;

	flags = O_RDWR | O_CREAT;
	while ((c = getopt(argc, argv, "e")) != -1) {
		switch (c) {
		case 'e':
			flags |= O_EXCL;
			break;
		default:
			break;
		}
	}

	if (optind != argc -1 ) {
		fprintf(stderr, "<%s> usage: mqceate [ -e ] <name>\n", __func__);
		exit(1);
	}

	mqd = mq_open(argv[optind], flags, S_IRUSR | S_IWUSR, NULL);
	if (mqd == -1) {
		fprintf(stderr, "<%s> error mq_open\n", __func__);
		perror("mq_open");
		exit(2);
	} else {
		mq_close(mqd);
	}

	return 0;
}
