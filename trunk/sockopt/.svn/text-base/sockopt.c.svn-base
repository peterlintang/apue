
/*
 *  test the optiong of sock is supported or not
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/tcp.h>

union val {
	int	i_val;
	long	l_val;
	char	c_val[10];
	struct linger linger_val;
	struct timeval timeval_val;
};


char *sock_str_flag(union val *, int);
char *sock_str_int(union val *, int);
char *sock_str_linger(union val *, int);
char *sock_str_timeval(union val *, int);

struct sock_opts {
	char	*opt_str;
	int	opt_level;
	int	opt_name;
	char	*(*opt_val_str)(union val *, int);
} sock_opts[] = {
	"SO_DEBUG",	SOL_SOCKET, SO_DEBUG, 	  sock_str_flag,
	"SO_BROADCAST", SOL_SOCKET, SO_BROADCAST, sock_str_flag,
	"SO_DONTROUTE", SOL_SOCKET, SO_DONTROUTE, sock_str_flag,
	"SO_ERROR",	SOL_SOCKET, SO_ERROR,	  sock_str_int,
	"SO_KEEPALIVE", SOL_SOCKET, SO_KEEPALIVE, sock_str_flag,
	"SO_LINGER", 	SOL_SOCKET, SO_LINGER,	  sock_str_linger,
	"SO_OOBINLINE", SOL_SOCKET, SO_OOBINLINE, sock_str_flag,
	"SO_RCVBUF",	SOL_SOCKET, SO_RCVBUF,	  sock_str_int,
	"SO_SNDBUF",	SOL_SOCKET, SO_SNDBUF,	  sock_str_int,
	NULL, 		0,		0,		NULL
};

static char strres[128];


int main(int argc, char *argv[])
{
	int	fd;
	int	len;
	int	ret;
	struct sock_opts *ptr;
	union val val;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		perror("socket");
		exit(1);
	} else {
		printf("fd: %d\n", fd);
	}

	for (ptr = sock_opts; ptr->opt_str != NULL; ptr++) {
		printf("%s:", ptr->opt_str);
		if (ptr->opt_val_str == NULL) {
			printf("(undefined)\n");
		} else {
			len = sizeof(val);
			if ((ret = getsockopt(fd, ptr->opt_level, ptr->opt_name, &val, &len)) == -1) {
//			if (getsockopt(fd, SOL_SOCKET, SO_DEBUG, &val, len) == -1) {
				perror("getsockopt");
				continue;
			} else {
				printf("default = %s\n", (*ptr->opt_val_str)(&val, len));
			}
		}
	}

	return 0;
}

char *sock_str_flag(union val *ptr, int len)
{
	if (len != sizeof(int))
		snprintf(strres, sizeof(strres), "size (%d) not sizeof(int)", len);
	else
		snprintf(strres, sizeof(strres), "%s", (ptr->i_val == 0) ? "off" : "on");
	return strres;
}

char *sock_str_int(union val *ptr, int len)
{
	if (len != sizeof(int))
		snprintf(strres, sizeof(strres), "size (%d) not sizeof(int)", len);
	else
		snprintf(strres, sizeof(strres), "%d", ptr->i_val);
	return strres;
}

char *
sock_str_linger(union val *ptr, int len)
{
        struct linger   *lptr = &ptr->linger_val;

        if (len != sizeof(struct linger))
                snprintf(strres, sizeof(strres),
                                 "size (%d) not sizeof(struct linger)", len);
        else
                snprintf(strres, sizeof(strres), "l_onoff = %d, l_linger = %d",
                                 lptr->l_onoff, lptr->l_linger);
        return(strres);
}

char *
sock_str_timeval(union val *ptr, int len)
{
        struct timeval  *tvptr = &ptr->timeval_val;

        if (len != sizeof(struct timeval))
                snprintf(strres, sizeof(strres),
                                 "size (%d) not sizeof(struct timeval)", len);
        else
                snprintf(strres, sizeof(strres), "%d sec, %d usec",
                                 tvptr->tv_sec, tvptr->tv_usec);
        return(strres);
}

