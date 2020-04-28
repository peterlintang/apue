
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	mqd_t mqd;
	struct mq_attr attr;

	if (argc != 2)
	{
		fprintf(stdout, "usage: %s name\n", argv[0]);
		exit(0);
	}


	mqd = mq_open(argv[1], O_RDONLY);

	memset(&attr, 0, sizeof(attr));
	mq_getattr(mqd, &attr);
	fprintf(stdout, "posix msg : %s attr\n", argv[1]);
	fprintf(stdout, "max msg: %ld, msg size: %ld, cur msgs: %ld\n",
					attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);

	mq_close(mqd);

	return 0;
}
