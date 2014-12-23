
/*
 * implement the unix domain's client
 * filename: 	udsock-client.h
 */

#ifndef JOHNLIN_UDSOCK_CLIENT_H__
#define JOHNLIN_UDSOCK_CLIENT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

typedef struct __unix_sock_client {
	int	conn_sock;
	char	*path;
} unix_sock_client;

unix_sock_client *create_unix_sock_client(const char *pathname);
void destroy_unix_sock_client(unix_sock_client **clientpp);
int unix_sock_connect(unix_sock_client *client);
int unix_sock_recv_client(unix_sock_client *client,
                                char *buf, unsigned int len);
int unix_sock_send_client(unix_sock_client *client,
                                char *buf, unsigned int len);

#endif	// JOHNLIN_UDSOCK_CLIENT_H__
