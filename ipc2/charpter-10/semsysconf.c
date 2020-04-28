
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	fprintf(stdout, "SEM_NSEMS_MAX = %ld, SEM_VALUE_MAX = %ld\n",
					sysconf(_SC_SEM_NSEMS_MAX), sysconf(_SC_SEM_VALUE_MAX));
	return 0;
}
