
/*
 *发送消息到system v消息队列，
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
	fprintf(stdout, "usage: %s <pathname> <#bytes> <type>\n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	int ret = 0;
	int len = 0;
	long type = 0;
	int msgid;
	struct msgbuf {
		long mtype;
		char mtext[1];
	}f;
	struct msgbuf *ptr = NULL;

	if (argc != 4)
		usage(argv[0]);

	len = atoi(argv[2]);
	type = atoi(argv[3]);

	ptr = calloc(sizeof(long) + len, sizeof(char));
	ptr->mtype = type;

	msgid = msgget(ftok(argv[1], 0), S_IWUSR);
	if (msgid == -1)
	{
		fprintf(stderr, "msgget failed: %s\n", strerror(errno));
		exit(1);
	}

	ret = msgsnd(msgid, ptr, len, 0);
	if (ret == -1)
	{
		fprintf(stderr, "msgsnd failed: %s\n", strerror(errno));
		exit(1);
	}

	free(ptr);

	return 0;
}




