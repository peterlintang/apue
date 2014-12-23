/*
 *   for debug  with debug.c in src
 */

#ifndef debug_H
#define debug_H

#include <pthread.h>
#define DEBUG_SOURCE "Default"

# ifndef CURRENT_TIME
#include <time.h>
static inline char * __current_time() { time_t tm = time(NULL); static char timebuf[26]; strcpy(timebuf, ctime(&tm) + 4); timebuf[15] = 0; return timebuf; }
#define CURRENT_TIME __current_time()
# endif

#include <sys/time.h>
static struct timeval tv = { .tv_sec = 0, .tv_usec = 0 };
static inline long int __tsec () { gettimeofday(&tv, NULL); return tv.tv_sec; }
static inline long int __tusec () { return tv.tv_usec; }

extern int DebugLevel;

#define DOFF	0
#define DFATAL	1
#define DERROR 	2
#define DWARN	3
#define DINFO	4
#define DDEBUG	5
#define DALL	6

#define DERR	2
#define DMSG	4

#define DEBUG_LEVELS { "DOFF", "DFATAL", "DERROR", "DWARN", "DINFO", "DDEBUG", "DALL" };

# ifndef __DEBUG__

#define DEBUGP(TYPE, FUNC, FORMAT, ARGS...) ;

# else

static inline char* __get_type_label(int type) { char *labels[] = DEBUG_LEVELS; return labels[type] + 1; }

#include <unistd.h>
#define DEBUGP(TyPE, FUNC, FORMAT, ARGS...)	{  	\
	switch (DebugLevel) {				\
	default :					\
	case DOFF: break;				\
	case DALL:					\
	case DFATAL:					\
	case DERROR:					\
		if (TYPE <= DebugLevel)			\
			fprintf(stderr, "[%s][%lu.%06lu][%u@%X] %-5s [%s:%s] " FORMAT "\n", CURRENT_TIME, __tsec(), __tusec(), (int)getpid() (int)pthread_self(), __get_type_label(TYPE), DEBUG_SOURCE, FUNC, ##ARGS); 			 \
	}						\
}			

# endif

#endif /* debug_H */
