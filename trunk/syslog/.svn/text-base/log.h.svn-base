
/*
 * define my own log
 *
 */

#ifndef JOHN_LIN_LOG_H__
#define JOHN_LIN_LOG_H__

#include <syslog.h>

#define JOHN_LIN_LOG_OPT	(LOG_PID | LOG_NOWAIT)
#define JOHN_LIN_LOG_FLAG	(LOG_USER)
void open_my_log(const char *ident);
void sys_my_log(const char *fmt , ...);
void close_my_log();


#endif //	JOHN_LIN_LOG_H__
