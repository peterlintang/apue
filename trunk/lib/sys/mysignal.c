/*
 * this implements the interfaces of signals
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>	/* for strftime and localtime */
#include <sys/time.h>	/* for gettimeofday */
#include <string.h>	/* for memcpy */
#include <strings.h>	/* fore bzero */
#include <signal.h>

#include "mysignal.h"
#include "simple_list.h"	/* we use the simple list interfaces 
				rather than list interfaces, 
				for testing the simple list interfaces */

/* we only consider linux OS */
#if defined (linux)	
# define SIGNALS_ENTRIES_MAXNUM __SIGRTMAX
#else 
# error unable to determine the maxinum number of signals availabe on platform
# define SIGNALS_ENTRIES_MAXNUM
#endif

/* 
 * how to protect the global list for reentry ?
 */
int last_signal = 0;
static struct sigaction saved_action_table[SIGNALS_ENTRIES_MAXNUM];
static simple_list_t *signal_handler_table[SIGNALS_ENTRIES_MAXNUM];


/* 
 * signal handler
 **/
void signal_handler(int32_t signum)
{
	static struct sigaction new_action;
	static struct sigaction old_action;
	static struct timeval tv;
	static char str_time[40];

	bzero(&new_action, sizeof(new_action));
	bzero(&old_action, sizeof(old_action));
	new_action.sa_handler = &signal_handler; /* is it OK to use signal_handler */
	if (sigaction(signum, &new_action, &old_action) == -1) {
		fprintf(stderr, "%s: no sigaction for signum %d\n",
				__func__,
				signum);
		return ;
	}

	if (new_action.sa_handler != old_action.sa_handler) {
		memcpy(&saved_action_table[signum], 
			&old_action, 
			sizeof(old_action));
		return ;
	}

	last_signal = signum;
	gettimeofday(&tv, NULL);
	strftime(str_time, 
		sizeof(str_time), 
		"%Y-%m-%d %H:%M:%S", 
		localtime((time_t *) tv.tv_sec));

	/* execut it */
	if (signal_handler_table[signum]) {
		simple_list_item_t *item = \
			_get_simple_list_head(signal_handler_table[signum]);
		while (item) {
			signal_cb_func func = (signal_cb_func) item->value;
			(*func)(signum);
			item = _next_simple_list_item(item);
		}
	} else if (saved_action_table[signum].sa_handler) {
		(*saved_action_table[signum].sa_handler)(signum);
	} else {
		fprintf(stderr, "%s: no handler routine for signal: %d! \
				exiting...\n", 
				__func__, 
				signum);
		exit(0);
	}
}

/* 
 * signals interfaces 
 */
void add_signal_handler(int signum, signal_cb_func func)
{
	simple_list_item_t *new = NULL;
	simple_list_t *list = NULL;

	if (!signal_handler_table[signum]) {		/* for the first time we register it */
		list = _new_simple_list();
		if (!list) {
			fprintf(stderr, "%s: cannot allocate new \
					simple list for signal\n", 
					__func__);
			return ;
		}
		signal_handler_table[signum] = list;

		signal_handler(signum);
	}
	
	new = _new_simple_list_item(func);		/* 
							 * for the not first time register signal handler 
							 * just add it to the tail of the list 
							 **/
	if (!_insert_item_to_simple_list_after(signal_handler_table[signum], 
					new, 
					NULL)) {
		_destroy_simple_list_item(&new);
		fprintf(stdout, "%s: cannot insert signal handler to table\n", 
			__func__);
	}
}

