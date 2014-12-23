
/*
 *
 *  print a process 's resource 
 *  limits
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

void print_rlimit(enum __rlimit_resource resource)
{
	struct rlimit 	rlimit;

	if (getrlimit(resource, &rlimit)) {
		perror("getrlimit");
	} else {
		fprintf(stdout, "cur: %-10ld", rlimit.rlim_cur);
		fprintf(stdout, "max: %-10ld", rlimit.rlim_max);
	}
}

int main(int argc, char *argv[])
{
	fprintf(stdout, "\t*********resource limit**************\n");
	
	fprintf(stdout, "RLIMIT_AS\n");
	print_rlimit(RLIMIT_AS);
	fprintf(stdout, "\n");

	fprintf(stdout, "RLIMIT_CORE\n");
	print_rlimit(RLIMIT_CORE);
	fprintf(stdout, "\n");

	fprintf(stdout, "RLIMIT_CPU\n");
	print_rlimit(RLIMIT_CPU);
	fprintf(stdout, "\n");

	fprintf(stdout, "RLIMIT_DATA\n");
	print_rlimit(RLIMIT_DATA);
	fprintf(stdout, "\n");

	fprintf(stdout, "RLIMIT_FSIZE\n");
	print_rlimit(RLIMIT_FSIZE);
	fprintf(stdout, "\n");

	fprintf(stdout, "RLIMIT_LOCKS\n");
	print_rlimit(RLIMIT_LOCKS);
	fprintf(stdout, "\n");

	fprintf(stdout, "RLIMIT_MEMLOCK\n");
	print_rlimit(RLIMIT_MEMLOCK);
	fprintf(stdout, "\n");

	fprintf(stdout, "RLIMIT_NOFILE\n");
	print_rlimit(RLIMIT_NOFILE);
	fprintf(stdout, "\n");

	fprintf(stdout, "RLIMIT_NPROC\n");
	print_rlimit(RLIMIT_NPROC);
	fprintf(stdout, "\n");

	fprintf(stdout, "RLIMIT_RSS\n");
	print_rlimit(RLIMIT_RSS);
	fprintf(stdout, "\n");

	/* no included  */
/*
	fprintf(stdout, "RLIMIT_SBSIZE\n");
	print_rlimit(RLIMIT_SBSIZE);
	fprintf(stdout, "\n");
*/
	fprintf(stdout, "RLIMIT_STACK\n");
	print_rlimit(RLIMIT_STACK);
	fprintf(stdout, "\n");

	/* no included */
/*
	fprintf(stdout, "RLIMIT_VMEM\n");
	print_rlimit(RLIMIT_VMEM);
	fprintf(stdout, "\n");
*/
	return 0;
}
