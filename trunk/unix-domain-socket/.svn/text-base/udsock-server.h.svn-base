
/*
 * implements the unix domain sock server interfaces
 * filename:	udsock-server.h
 */

#ifndef JOHN_LIN_UDSOCK_SERVER_H__
#define JOHN_LIN_UDSOCK_SERVER_H__
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "udsock-client.h"


typedef struct __unix_sock_server {
	int	listen_sock;
	int	backlog;
	char	*path;
} unix_sock_server;

unix_sock_server *create_unix_sock_server(const char *pathname, int backlog);
void destroy_unix_sock_server(unix_sock_server **serverpp);

unix_sock_client *unix_sock_accept_server(unix_sock_server *server);

int unix_sock_send_server(unix_sock_client *client, 
				char *buf, unsigned int len);

int unix_sock_recv_server(unix_sock_client *client, 
				char *buf, unsigned int len);

#endif 	// JOHN_LIN_UDSOCK_SERVER_H__
