
/*
 *创建一个posix 消息队列，名字有参数指定
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>

#include <unistd.h>
#include <errno.h>

#define FILE_MODE S_IRUSR | S_IWUSR

static void usage(char *proc)
{
	fprintf(stdout, "usage: %s [-e] [-m maxmsg -z msgsize] <name>\n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	int c;
	int flags;
	mqd_t mqd;
	struct mq_attr attr;

	flags = O_RDWR | O_CREAT;
	memset(&attr, 0, sizeof(attr));

	while ((c = getopt(argc, argv, "em:z:")) != -1)
	{
		switch (c)
		{
			case 'e':
				flags |= O_EXCL;
				break;
			case 'm':
				attr.mq_maxmsg = atoi(optarg);
				break;
			case 'z':
				attr.mq_msgsize = atoi(optarg);
				break;
		}
	}

	if (optind != argc - 1)
	{
		usage(argv[0]);
	}

	fprintf(stdout, "maxmsg: %ld, msgsize: %ld, name: %s\n", attr.mq_maxmsg, attr.mq_msgsize, argv[optind]);

	mqd = mq_open(argv[optind], flags, FILE_MODE, &attr);
	if (mqd == -1)
	{
		fprintf(stderr, "open failed: %s\n", strerror(errno));
		exit(1);
	}
	mq_close(mqd);

	return 0;
}


