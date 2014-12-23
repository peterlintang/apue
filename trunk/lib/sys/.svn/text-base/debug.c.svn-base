/*
 * this implements the debug interface,
 * which will write the stdout stderr 
 * debug info into the debug file
 */
#include <stdio.h>
#include <stdlib.h>		/* for free */
#include <unistd.h>		/* for dup2 */
#include <sys/stat.h>
#include <errno.h>


#include "debug.h"



static void debug_log_dir(const char *dir)
{
	if (dir) {
		char *debug_out;
		char *debug_err;

		asprintf(&debug_out, "%s/debug.out", dir);
		asprintf(&debug_err, "%s/debug.err", dir);
		FILE *out = fopen(debug_out, "a");
		FILE *err = fopen(debug_err, "a");
		free(debug_out);
		free(debug_err);

		if (out && err &&
			dup2(fileno(out), fileno(stdout)) >= 0 &&
			dup2(fileno(err), fileno(stderr)) >= 0) {
			setvbuf(out, NULL, _IOLBF, BUFSIZ);
			setvbuf(err, NULL, _IOLBF, BUFSIZ);
		} else {
			DEBUGP(DERR, "debug_log_dir", "unable to redirect \
				stdout & stderr to %s directory", dir);
			fclose(out);
			fclose(err);
		}
	}
}
