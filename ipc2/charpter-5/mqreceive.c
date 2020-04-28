
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <unistd.h>

static void usage(char *proc)
{
	fprintf(stdout, "usage: %s [-n] <name>\n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	int c;
	int flags;
	mqd_t mqd;
	size_t n = 0;
	char *ptr = NULL;
	unsigned int prio = 0;
	struct mq_attr attr;

	flags = O_RDONLY;
	while ((c = getopt(argc, argv, "n")) != -1)
	{
		switch (c) 
		{
			case 'n':
				flags |= O_NONBLOCK;
				break;
		}
	}

	if (optind != argc - 1)
		usage(argv[0]);

	mqd = mq_open(argv[optind], flags);

	memset(&attr, 0, sizeof(attr));
	mq_getattr(mqd, &attr);

	ptr = calloc(attr.mq_msgsize, sizeof(char));

	n = mq_receive(mqd, ptr, attr.mq_msgsize, &prio);
	fprintf(stdout, "read %ld bytes, priority = %u\n", (long)n, prio);

	free(ptr);
	mq_close(mqd);

	return 0;

}
