
/*
 *从system v消息队列读取消息，
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

#define MAXMSG	1024

static void usage(char *proc)
{
	fprintf(stdout, "usage: %s [-n] [-t type] <pathname>\n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	int c;
	int ret = 0;
	long type = 0;
	int flag = 0;
	int msgid;
	struct msgbuf {
		long mtype;
		char mtext[1];
	}f;
	struct msgbuf *ptr = NULL;

	while ((c = getopt(argc, argv, "nt:")) != -1)
	{
		switch (c)
		{
			case 'n':
				flag |= IPC_NOWAIT;
				break;
			case 't':
				type = atoi(optarg);
				break;
		}
	}

	if (optind != argc - 1)
		usage(argv[0]);

	ptr = calloc(MAXMSG + sizeof(long), sizeof(char));

	msgid = msgget(ftok(argv[1], 0), S_IRUSR);
	if (msgid == -1)
	{
		fprintf(stderr, "msgget failed: %s\n", strerror(errno));
		exit(1);
	}

	ret = msgrcv(msgid, ptr, MAXMSG, type, flag);
	if (ret == -1)
	{
		fprintf(stderr, "msgrcv failed: %s\n", strerror(errno));
		exit(1);
	}

	fprintf(stdout, "receive msg: type = %ld, bytes = %d\n", ptr->mtype, ret);

	free(ptr);

	return 0;
}




