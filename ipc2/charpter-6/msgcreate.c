
/*
 *创建system v消息队列，
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

static void usage(char *proc)
{
	fprintf(stdout, "usage: %s [-e] <pathname>\n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	int msgid;
	int oflags = 0;
	int c;

	oflags = S_IRUSR | S_IWUSR | IPC_CREAT;

	while ((c = getopt(argc, argv, "e")) != -1)
	{
		switch (c)
		{
			case 'e':
				oflags |= IPC_EXCL;
				break;
		}
	}

	if (optind != argc - 1)
		usage(argv[0]);

	msgid = msgget(ftok(argv[optind], 0), oflags);
	if (msgid == -1)
	{
		fprintf(stderr, "msgget failed: %s\n", strerror(errno));
		exit(1);
	}

	return 0;
}




