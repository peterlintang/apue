
#include "sysmsg.h"


#define MSG_W S_IWUSR

int main(int argc, char **argv)
{
	int	len;
	long 	type;
	int	msgid;
	int	oflag;
	struct msgbuf {			/* you need to define your struct msgbuf */
		long mtype;
		char mtext[8192];
	} *buff;

	oflag = MSG_W;

	if (argc != 4) {
		fprintf(stdout, "<%s> usage: \
			msgsnd <pathname> <#bytes> <type>\n", __func__);
		exit(1);
	}

	len = atoi(argv[2]);
	type = atoi(argv[3]);

	msgid = msgget(ftok(argv[1], 0), oflag);
	if (msgid == -1) {
		perror("msgget");
		exit(2);
	}

	buff = (struct msgbuf *)calloc(sizeof(long) + 8192, sizeof(char));
	buff->mtype = type;
	//buff->mtype = 5;

	msgsnd(msgid, buff, len, 0);

	return 0;
}
