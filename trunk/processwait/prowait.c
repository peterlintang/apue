
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	pid_t 	pid;
	int	status;

	if ((pid = fork()) < 0) {
		perror("fork");
		exit(-1);
	} else if (pid == 0) {
		fprintf(stdout, "in child : running\n");
//		abort();
	} else {
		fprintf(stdout, "in parent : running\n");
		fprintf(stdout, "waiting child ...\n");
		if (wait(&status) < 0)
			perror("wait");
		fprintf(stdout, "child exit status: %d\n", status);
	}

	return 0;
}
