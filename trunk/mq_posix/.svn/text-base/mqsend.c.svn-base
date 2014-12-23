
#include <stdio.h>
#include <stdlib.h>     /* for exit */
#include <mqueue.h>     /* for mqd_t & mq_open mq_close */
#include <sys/stat.h>   /* for S_IRUSR S_IWUSR */
#include <fcntl.h>      /* for O_xxx */
#include <unistd.h>     /* for getopt */

#define FILE_MODE S_IRUSR | S_IWUSR

int main(int argc, char **argv)
{
	mqd_t	mqd;
	void	*ptr;
	size_t	len;
	unsigned int  prio;
	int	retval;

	if (argc != 4) {
		fprintf(stdout, "<%s> usage: mqsend <name> <#bytes> <priority>\n", __func__);
		exit(1);
	}

	len = atoi(argv[2]);
	prio = atoi(argv[3]);

	mqd = mq_open(argv[1], O_WRONLY);
	if (mqd == -1) {
		perror("mq_open");
		exit(2);
	}

	ptr = calloc(len, sizeof(char));

	retval = mq_send(mqd, ptr, len, prio);
	if (retval) {
		perror("mq_send");
		exit(3);
	}

	mq_close(mqd);

	return 0;
}
