
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	pid_t pid;

	if ((pid = fork()) == 0) {
		if (execlp("ls", "ls", "-lh", (char *)0) < 0)
			fprintf(stdout, "execlp ls error\n");
	} else if (pid < 0) {
		perror("fork");
		exit(-1);
	} else {
		if (execlp("tree", "tree", "-a", (char *)0) < 0)
			fprintf(stdout, "execlp tree error\n");
	}
	return 0;
}
