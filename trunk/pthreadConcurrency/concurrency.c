
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main(int argc, char **argv)
{
	int	level;

	if (argc != 2) {
		fprintf(stdout, "<%s> usage: concurrency <level>\n", __func__);
		exit(1);
	}

	level = atoi(argv[1]);
	fprintf(stdout, "<%s> current concurrency: %d \n", __func__, pthread_getconcurrency());
	pthread_setconcurrency(level);
	fprintf(stdout, "<%s> new concurrency: %d \n", __func__, pthread_getconcurrency());

	return 0;
}
