
#include "sysmsg.h"

#define MAX_DATA 	(64 * 1024)
#define MAX_NMESG 	4096
#define MAX_NIDS	4096

struct mymesg {
	long 	mtype;
	char	mtext[MAX_DATA];
} mesg;

int max_mesg;

int main(int argc, char **argv)
{
	int i;
	int j;
	int msgid;
	int qid[MAX_NIDS];

	msgid = msgget(IPC_PRIVATE, S_IRUSR | S_IWUSR | IPC_CREAT);
	if (msgid == -1) {
		perror("msgget");
		exit(1);
	}

	mesg.mtype = 1;
	for (i = MAX_DATA; i > 0; i -= 128) {
		if (msgsnd(msgid, &mesg, i, 0) == 0) {
			fprintf(stdout, "<%s> maximum amount of \
				data per message = %d\n", __func__, i);
			max_mesg = i;
		}

		if (errno = EINVAL) {
			perror("msgsnd");
			exit(2);
		}
	}
		
}
