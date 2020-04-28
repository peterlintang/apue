
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int ret = 0;
	int msgid;
	struct msqid_ds info;
	struct msgbuf {
		long mtype;
		char mtext[1];
	} buff;

	memset(&info, 0, sizeof(info));
	memset(&buff, 0, sizeof(buff));

	msgid = msgget(IPC_PRIVATE, S_IRUSR | S_IWUSR | IPC_CREAT);
	if (msgid == -1)
	{
		fprintf(stderr, "msgget failed: %s\n", strerror(errno));
		exit(1);
	}

	buff.mtype = 1;
	buff.mtext[0] = 1;

	ret = msgsnd(msgid, &buff, 1, 0);
	if (ret == -1)
	{
		fprintf(stderr, "msgsnd failed: %s\n", strerror(errno));
		exit(1);
	}

	msgctl(msgid, IPC_STAT, &info);

	fprintf(stdout, "read-write: %03o, cbytes = %lu, qnum = %lu, qbytes = %lu\n",
				info.msg_perm.mode & 0777, (unsigned long)info.msg_cbytes,
				(unsigned long)info.msg_qnum, (unsigned long)info.msg_qbytes);

	system("ipcs -q");

	msgctl(msgid, IPC_RMID, NULL);

	return 0;
}


