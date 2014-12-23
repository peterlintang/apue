
/*
 *
 * this is for setting debug output file
 *
 */
#include <stdio.h>
#include <stdlib.h>

void debugLogDir(char *dir)
{
	if (dir) {
		char *dErr, *dOut;
		asprintf(&dErr, "%s/debug.err", dir);
		asprintf(&dOut, "%s/debug.out", dir);
		
		FILE *out = fopen(dOut, "a");
		FILE *err = fopen(dErr, "a");

		free(dOut);
		free(dErr);

		if (out && err &&
			dup2(flieno(out), fileno(stdout)) >= 0 &&
			dup2(fileno(err), fileno(stderr)) >= 0 ) {
			setvbuf(out, NULL, _IOLBF, BUFSIZ);
			setvbuf(err, NULL, _IOLBF, BUFSIZ);
		} else {
			DEBUGP(DERR, "debugLogDir", "unable to redirect STDOUT & STDERR to %s directory", dir);
		}
	}
}
