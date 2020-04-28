
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <unistd.h>

static void usage(char *proc)
{
	fprintf(stdout, "usage: %s <name> <bytes> <priority>\n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	mqd_t mqd;
	size_t len;
	char *ptr;
	unsigned int prio;

	if (argc != 4)
		usage(argv[0]);

	len = atoi(argv[2]);
	prio = atoi(argv[3]);

	mqd = mq_open(argv[1], O_WRONLY);

	ptr = calloc(len, sizeof(char));

	mq_send(mqd, ptr, len, prio);

	free(ptr);
	mq_close(mqd);

	return 0;

}
