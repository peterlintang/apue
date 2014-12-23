
#include <stdio.h>
#include <stdlib.h>

#include <syslog.h>

int main(int argc, char *argv[])
{
	openlog("john lin", LOG_PID | LOG_NOWAIT, LOG_USER);

	syslog(LOG_INFO, "hello world");

	closelog();

	return 0;
}
