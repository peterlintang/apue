
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>

#include <unistd.h>


int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stdout, "usage: %s name\n", argv[1]);
		exit(0);
	}

	mq_unlink(argv[1]);

	return 0;
}
