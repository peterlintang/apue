#include <fcntl.h>
#include "apue.h"

#ifdef DEBUG
#define dprintf(fmt, args...) fprintf(stdout, fmt, ##args)
#else
#define dprintf(fmt, args...) 
#endif

#define errprintf(fmt, args...) fprintf(stderr, fmt, ##args)

#define TYPESIZE 12
#define BUFSIZE 1024


void readwirelessmod(char *path)
{
	int fd;
	char buf[1024];
	char *wsmode;
	char *bridgename=NULL;
	char *bridge_A=NULL;
	char *bridge_B=NULL;

	memset(buf, 0, 1024);
	if ((fd = open(path, O_RDONLY)) < 0)
	{
		errprintf("open %s error\n", path);
		exit(1);
	}
	if (read(fd, buf, 1024) < 0)
	{
		errprintf("read %s error\n", path);
		exit(1);
	}
}

int
main(int argc, char *argv[])
{
	char *type = NULL;
	char *buf  = NULL;
	char *SSID = "RT2860AP";

	type = malloc(TYPESIZE);
	buf  = malloc(BUFSIZE);
	if (!type || !buf)
	{
		errprintf("malloc error\n");
		exit(1);
	}
	else
	{
		memset(type, 0, TYPESIZE);
		memset(buf, 0, TYPESIZE);
	}

	/*read wirelessmod.conf*/

	sprintf(type, "ws-none", 7);

	if (!strncmp(type, "ws-", 3))
	{
		char *typebuf = &type[3];
		if (!strncmp(typebuf, "none", 4))
		{
			sprintf(buf, "/usr/sbin/softap_daemon down &>/dev/null\n");
			sprintf(buf + strlen(buf), "/usr/sbin/iwpriv ra0 set EncrypType=NONE\n");
			sprintf(buf + strlen(buf), "/usr/sbin/iwpriv ra0 set AuthMode=OPEN\n");
			sprintf(buf + strlen(buf), "/usr/sbin/iwpriv ra0 set SSID=%s\n", SSID);
			system(buf);
		}
		else if (!strncmp(typebuf, "wep40", 5))
		{
		}
		else if (!strncmp(typebuf, "wep128", 6))
		{
		}
		else if (!strncmp(typebuf, "wpapsk", 6))
		{
		}
		else if (!strncmp(typebuf, "wpaeap", 6))
		{
		}
		else if (!strncmp(typebuf, "bridge", 6))
		{
		}
		else if (!strncmp(typebuf, "router", 5))
		{
		}
		else if (!strncmp(typebuf, "closed", 5))
		{
		}
		else
		{
			dprintf("nothing to do\n");
		}

		system("sh /usr/sbin/persist /etc/wireless/*");

	}
	else
	{
		errprintf("Unsupportd type: %s failed.\n", type);
		exit(1);
	}

	fprintf(stdout, "Success! Configuration saved.");

	exit(0);
}






