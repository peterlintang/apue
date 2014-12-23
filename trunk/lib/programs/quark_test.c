
/*
 * have a test of quark interfaces
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "quark.h"

int show_quark_func(void *data)
{
	fprintf(stdout, "%s : hello world\n", __func__);
	return 1;
}

int main(int argc, char *argv[])
{
	quark_t *quark = _new_quark(show_quark_func, NULL);
	if (!_spin_quark(quark))
		fprintf(stderr, "_spin_quark error\n");
	sleep(1);
	_stop_quark(quark, 100);
	_destroy_quark(&quark);
	return 0;
}
