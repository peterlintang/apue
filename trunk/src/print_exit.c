
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void print_exit(int status)
{
	if (WEXITSTATUS(status)) 
		fprintf(stdout, "normal termination, exit status = %d\n", WEXITSTATUS(status));
	else if (WTERMSIG(status))
		fprintf(stdout, "abnormal termination, signal number = %d%s\n", WTERMSIG(status),
#ifdef WCOREDUMP
						WCOREDUMP(status) ? " (core file generated)" : "");
#else
						"");
#endif 
	else if (WIFSTOPPED(status))
		fprintf(stdout, "child stopped, signal number = %d\n", WSTOPSIG(status));
	else 
		fprintf(stdout, "unknow status = %d\n", status);
}
