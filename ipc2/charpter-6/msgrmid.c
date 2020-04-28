
/*
 *删除system v消息队列，
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
	fprintf(stdout, "usage: %s  <pathname>\n", proc);
	exit(0);
}

int main(int argc, char *argv[])
{
	int ret = 0;
	int msgid;

	if (argc != 2)
		usage(argv[0]);

	msgid = msgget(ftok(argv[1], 0), 0);
	if (msgid == -1)
	{
		fprintf(stderr, "msgget failed: %s\n", strerror(errno));
		exit(1);
	}

	ret = msgctl(msgid, IPC_RMID, NULL);
	if (ret == -1)
	{
		fprintf(stderr, "msgctl failed: %s\n", strerror(errno));
		exit(1);
	}

	return 0;
}




