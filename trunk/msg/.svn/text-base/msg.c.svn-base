
/*
 * creat msg and write @"hello world"
 * to the msg, need root or admin auth
 * last we get the message from msg
 */

#include "apue.h"
//#include <sys/ipc.h>
#include <linux/msg.h>

int main(int argc, char *argv[])
{
	int	i;
	int	msgid;
	char	buf[16];

	for (i = 0; i < 5; i++) {
		fprintf(stdout, "i: %d\n", i);
		if ((msgid = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL)) == -1) {
			perror("msgget");
			exit(-1);
		}
		fprintf(stdout, "msgid: %d\n", msgid);
		msgctl(msgid, IPC_RMID, NULL);
	}

	fprintf(stdout, "\n\tsecond time\t\n");
	for (i = 0; i < 5; i++) {
		fprintf(stdout, "i: %d\n", i);
		if ((msgid = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL)) == -1) {
			perror("msgget");
			exit(-1);
		}
		fprintf(stdout, "msgid: %d\n", msgid);
		if (msgsnd(msgid, "hello world", 12, IPC_NOWAIT) == -1) {
			perror("msgsnd");
			exit(-1);
		}
	}
	
	fprintf(stdout, "\t\nget msg from last msg\t\n");
	if (msgrcv(msgid, buf, 12, 0, MSG_NOERROR) == -1) {
		perror("msgrcv");
		exit(-1);
	} else {
		fprintf(stdout, "get message: %s\n", buf);
	}

	return 0;
}
