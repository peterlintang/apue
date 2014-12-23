
/*
 * fork many process as possible
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	volatile int 	i = 0;
	pid_t 		pid;

	while (1) {
		if ((pid = fork()) < 0) {
			perror("fork error");
			exit(-1);
		} else if (pid == 0) {
			sleep(8);
			exit(0);
		} else {
			i++;
			fprintf(stdout, "pid : %-8d max: %-8d\n", pid, i);
			usleep(4);
		}
	}

	return 0;
}
