#include "apue.h"

#define	MAXARGC		50  /* max number of arguments in buf */
#define	WHITE		" \t\n"	/* white space for tokenizing arguments */

/*
 * buf[] contains white-space-separated arguments. we convert it to an
 * argv-style array of pointers, and call the user's function (optfunc)
 * to process the array. we return -1 if there's a problem parsing buf,
 * else we return whatever optfunc() returns. note that user's buf[]
 * array is modified (nulls placed after each token).
 *
 */
int
buf_args(char *buf, int (*optfunc)(int , char **))
{
	char	*ptr, *argv[MAXARGC];
	int	argc;
	
	if (strtok(buf, WHITE) == NULL)
		return (-1);
	argv[argc = 0] = buf;
	while ((ptr = strtok(NULL, WHITE)) != NULL)
	{
		if (++argc >= MAXARGC - 1)
			return (-1);
		argv[argc] = ptr;
	}
	argv[++argc] = NULL;

	/*
	 * since argv[] pointers point into the user's buf[],
	 * user's function can just copy the pointers, even
	 * thought argv[] array will disappear on return.
	 */
	return((*optfunc)(argc, argv));
}
