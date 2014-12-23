
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <asm-generic/unistd.h>

int main(int argc, char **argv)
{
	pid_t pid;

	pid = sys_getpid();
	fprintf(stdout, "pid : %d\n", pid);
	
	return 0;
}
