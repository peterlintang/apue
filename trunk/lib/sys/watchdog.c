/*
 * this implements the watch dog interfaces
 * which is mostly used in embeded system
 * Peter K Lee 's corenova for more detail code 
 */

#include <stdio.h>
//#include <sys/stat.h>
#include <fcntl.h>		/* for O_RDWR */
#include <errno.h>		/* for errno */

#include <linux/watchdog.h>	/* for WDIOC_GETTIMEOUT WDIOC_SETTIMEOUT */

#include "watchdog.h"

const char wdt_device[] = "/dev/watchdog";

int _enable_wdt(const char *wdt_dev, int timeout)
{
	int fd = 0;

	if (!wdt_dev)
		wdt_dev = wdt_device;

	if ((fd = open(wdt_dev, O_RDWR | O_SYNC)) == -1) {
		int err = errno;
		fprintf(stderr, "%s: failed to open %s(%d)\n", 
				__func__,
				wdt_dev,
				err);
		return -1;
	}

	if (ioctl(fd, WDIOC_SETTIMEOUT, &timeout) == -1) {
		int err = errno;
		fprintf(stderr, "%s: failed to set %s timeout %d(%d)\n",
				__func__,
				wdt_dev,
				timeout,
				err);
		close(fd);
		return -1;
	}

	return fd;
}

int _disable_wdt(int fd)
{
	write(fd, 'V', 1);
	if (close(fd) == -1) {
		int err = errno;
		fprintf(stderr, "%s: cannot close wdt device %d(%d)\n",
				__func__,
				fd,
				err);
		return -1;
	}

	return 0;
}

int _set_timeout_wdt(int fd, int timeout)
{
	if (ioctl(fd, WDIOC_SETTIMEOUT, &timeout) == -1) {
		int err = errno;
		fprintf(stderr, "%s: ioctl error: %d\n",
				__func__,
				err);
		return -1;
	}
	return 0;
}

int _get_timeout_wdt(int fd, int *timeout_ptr)
{
	if (ioctl(fd, WDIOC_GETTIMEOUT, timeout_ptr) == -1) {
		int err = errno;
		fprintf(stderr, "%s: ioctl error: %d\n",
				__func__,
				err);
		return -1;
	}
	return 0;
}

int _keepalive_wdt(int fd)
{
	if (ioctl(fd, WDIOC_KEEPALIVE, NULL) == -1) {
		int err = errno;
		fprintf(stderr, "%s: ioctl error: %d\n",
				__func__,
				err);
		return -1;
	}
	return 0;
}

