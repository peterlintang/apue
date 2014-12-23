
#include "sysmsg.h"

#define MSG_R S_IRUSR

#define MAXMSG	(8192 + sizeof(long))

int main(int argc, char **argv)
{
	int	c;
	int	flag;
	int	msgid;
	long	type;
	ssize_t	n;
	struct msgbuf {
		long mtype;
		char mtext[8192];
	} *buff; 

	type = 0;
	flag = 0;

	while ((c = getopt(argc, argv, "nt:")) != -1) {
		switch (c) {
		case 'n':
			flag |= IPC_NOWAIT;
			break;
		case 't':
			type = atol(optarg);
			break;
		default:
			break;
		}
	}

	if (optind != argc -1) {
		fprintf(stdout, "<%s> usage: msgrcv [ -n ] [ -t type ] <pathname>\n", __func__);
		exit(1);
	}

	msgid = msgget(ftok(argv[optind], 0), MSG_R);
	if (msgid == -1) {
		perror("msgget");
		exit(2);
	}

//	buff = malloc(MAXMSG);
	buff = malloc(sizeof(struct msgbuf));
	if (!buff) {
		perror("malloc");
		exit(3);
	}

	n = msgrcv(msgid, buff, 8192, type, flag);
	fprintf(stdout, "<%s> read %d bytes type = %ld\n", __func__, n, buff->mtype);

	return 0;
}
