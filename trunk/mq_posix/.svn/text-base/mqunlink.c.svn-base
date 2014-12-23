
#include <stdio.h>
#include <stdlib.h>     /* for exit */
#include <mqueue.h>     /* for mqd_t & mq_open mq_close */
#include <sys/stat.h>   /* for S_IRUSR S_IWUSR */
#include <fcntl.h>      /* for O_xxx */
#include <unistd.h>     /* for getopt */

#define FILE_MODE S_IRUSR | S_IWUSR

int main(int argc, char **argv)
{
	int retval;

	if (argc != 2) {
		fprintf(stdout, "<%s> usage: mqunlink <name>\n", __func__);
		exit(1);
	}

	retval = mq_unlink(argv[1]);
	if (retval) {
		perror("mq_unlink");
		exit(2);
	}

	return 0;
}
