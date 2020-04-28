
#include <stdio.h>
#include <stdlib.h>

#include <mqueue.h>

#include <unistd.h>

int main(int argc, char *argv[])
{
	fprintf(stdout, "MQ_OPEN_MAX = %ld, MQ_PRIO_MAX = %ld\n",
			sysconf(_SC_MQ_OPEN_MAX), sysconf(_SC_MQ_PRIO_MAX));
	return 0;
}
