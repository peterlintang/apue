#include "apue.h"
#include <sys/utsname.h>

#define DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...) fprintf(stdout, fmt, ##args)
#else
#define dprintf(fmt, args...)
#endif
#define errprintf(fmt, args...) fprintf(stderr, fmt, ##args)

#define NAMELEN 1024

int
main(int argc, char *argv[])
{
	char 	*buf;
	int 	reval;
	struct  utsname my_name;
	
	buf = malloc(NAMELEN);
	if (!buf)
	{
		errprintf("malloc falied\n");
		exit(1);
	}

	if (!gethostname(buf, NAMELEN))
	{
		printf("host name   :  %s\n", buf);
	}
	else
	{
		errprintf("gethostname error\n");
		exit(1);
	}

	if (uname(&my_name) < 0)
	{
		errprintf("uname error\n");
		exit(1);
	}
	else
	{
		printf("sysname	    :  %s\n", my_name.sysname);
		printf("nodename    :  %s\n", my_name.nodename);
		printf("release	    :  %s\n", my_name.release);
		printf("machine	    :  %s\n", my_name.machine);
		#if _UTSNAME_DOMAIN_LENGTH - 0
		# ifdef __USE_GNU
		printf("domainname  :  %s\n", my_name.domainname);
		# else
		printf("domainname  :  %s\n", my_name.__domainname);
		#endif //end of __USE_GNU
		#endif //end of _UTSNAME_DOMAIN_LEGNTH

	}

	exit(0);
}
