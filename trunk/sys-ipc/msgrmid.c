
#include "sysmsg.h"

int main(int argc, char **argv)
{
	int	msgid;

	if (argc != 2) {
		fprintf(stdout, "<%s> usage: msgrmid <pathname>\n", __func__);
		exit(1);
	}

	msgid = msgget(ftok(argv[1], 0), 0);
	if (msgid == -1) {
		perror("msgget");
		exit(2);
	}

	msgctl(msgid, IPC_RMID, NULL);
	
	return 0;
}
