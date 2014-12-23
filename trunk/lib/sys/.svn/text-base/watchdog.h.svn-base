/*
 * this implements the watch dog interfaces
 * which mostly used in embeded system
 *
 */

#ifndef __watchdog_H__
#define __watchdog_H__

#define WDT_DEFAULT_TIMEOUT	60

int _enable_wdt(const char *wdt_dev, int timeout);
int _disable_wdt(int fd);
int _set_timeout_wdt(int fd, int timeout);
int _get_timeout_wdt(int fd, int *timeout_ptr);
int _keepalive_wdt(int fd);

#endif
