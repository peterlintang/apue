
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int  argc, char **argv)
{
	fprintf(stdout, "<%s> SEM NUM MAX = %ld\tSEM VALUE MAX = %ld\n", 
			__func__,
			sysconf(_SC_SEM_NSEMS_MAX),
			sysconf(_SC_SEM_VALUE_MAX));
	return 0;
}

