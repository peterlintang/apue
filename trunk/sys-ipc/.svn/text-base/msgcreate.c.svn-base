
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>	/* for S_IXUSR */
#include <unistd.h>	/* for getopt */

#define SVMSG_MODE S_IRUSR | S_IWUSR

int main(int argc, char **argv)
{
	int	c;
	int	oflag;
	int	msqid;

	oflag = SVMSG_MODE | IPC_CREAT;

	while ((c = getopt(argc, argv, "e")) != -1) {
		switch (c) {
		case 'e':
			oflag |= IPC_EXCL;
			break;
		default:
			break;
		}
	}

	if (optind != argc - 1) {
		fprintf(stdout, "<%s> usage: msgcreate [ -e ] <pathname>\n", __func__);
		exit(1);
	}

	msqid = msgget(ftok(argv[1], 0), oflag);
	if (msqid == -1) {
		perror("msqget");
		exit(2);
	}

	return 0;
}
