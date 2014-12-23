
/*
 *
 * implements my log
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "log.h"

void open_my_log(const char *ident)
{
	openlog(ident, JOHN_LIN_LOG_OPT, JOHN_LIN_LOG_FLAG);
}

void sys_my_log(const char *fmt, ...)
{
}

void close_my_log(void)
{
	closelog();
}
