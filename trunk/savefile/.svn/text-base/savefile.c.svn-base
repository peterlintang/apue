#include <fcntl.h>
#include "apue.h"

#define DEBUG
#ifdef DEBUG
#define dprintf(fmt, args...) fprintf(stdout, fmt, ##args)
#else
#define dprintf(fmt, args...)
#endif

#define errprintf(fmt, args...) fprintf(stderr, fmt, ##args)

#define FILE_PATH "./show.conf"
#define BUFSIZE 1024

int 
main(int argc, char *argv[])
{
	int fd;
	char buf[BUFSIZE];

	memset(buf, 0, BUFSIZE);

	if ((fd = open(FILE_PATH, O_RDWR | O_CREAT, FILE_MODE)) < 0)
	{
		errprintf("no such file or can't open: %s\n", FILE_PATH);
		exit(1);
	}
	else
	{
		dprintf("open file: %s success\n", FILE_PATH);
	}
	
	sprintf(buf, "auto ra0\n");
	sprintf(buf + strlen(buf), "iface ra0 inet static\n");
	sprintf(buf + strlen(buf), "\taddress %s\n", "192.168.253.22");
	sprintf(buf + strlen(buf), "\tnetmask %s\n", "255.255.255.255");
	if (write(fd, buf, strlen(buf)) != strlen(buf))
	{
		errprintf("write error\n");
		exit(1);
	}
	else
	{
		dprintf("write ok\n");
	}

	close(fd);

	exit(0);
}
