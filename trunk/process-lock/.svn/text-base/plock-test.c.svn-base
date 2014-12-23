
/*
 * test our processes's lock
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "process-lock.h"

#define PROCESS_LOCK	"/tmp/john_lin_lock"
#define PROCESS_ID	0

int main(int argc, char *argv[])
{
	void *my_lock = NULL;

	my_lock = create_process_lock(PROCESS_LOCK, PROCESS_ID);
	if (!my_lock) {
		fprintf(stderr, "can not create process lock\n");
		exit(-1);
	}

	sleep(4);

	get_process_lock(my_lock);
	fprintf(stdout, "<%s>: get lock\n", __func__);
	sleep(4);
	fprintf(stdout, "send signal\n");
//	wait_process_cond(my_lock);
	broadcast_process_cond(my_lock);
//	fprintf(stdout, "wake up by other process\n");
	release_process_lock(my_lock);
	fprintf(stdout, "<%s>: release lock\n", __func__);
	
	fprintf(stdout, "destroying process lock\n");
	sleep(4);
	destroy_process_lock(&my_lock);
	fprintf(stdout, "done\n");

	return 0;
}
