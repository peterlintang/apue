/*
 * this implements the signals interfaces, 
 * see corenova 's /src/module/corenova/sys/signal.c
 * for orignal code
 */

#ifndef __signal_H__
#define __signal_H__

#include <signal.h>
#include <stdint.h>

extern int last_signal;

/* signal handler routine type */
typedef void (*signal_cb_func)(int32_t signum);

void signal_handler(int32_t signum);

/* signal interfaces */
void add_signal_handler(int signum, signal_cb_func func);

#endif
