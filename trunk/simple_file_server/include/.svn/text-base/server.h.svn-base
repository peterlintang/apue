/*
 * implement the server 
 */

#ifndef _SIMPLE_FILE_SERVER_SERVER_H
#define _SIMPLE_FILE_SERVER_SERVER_H

#include "common_addr.h"

typedef struct __server_t {
	char	*server_name;

	int 		listen_fd;
	unsigned int	back_log;
	server_addr_t		*server_addr;

	int	num_clients;
	client_t		*clients;

	struct __server_t 	*next;	/* not used now */
	struct __server_t	*prev;  /* not used now */
} server_t;

server_t *new_server(const char *server_name, unsigned int back_log, 
			const int af, const uint16_t port, const char *ipstr);

void destroy_server(server_t **ppserver);

char *set_server_name(server_t *server);

char *get_server_name(server_t *server);

unsigned int get_server_backlog(server_t *server);

unsigned int set_server_backlog(server_t *server);

client_t *add_client_to_server(server_t *server, client_t *new, client_t *after);

static inline client_t *add_client_to_server_at_head(server_t *server, client_t *new)
{
	return add_client_to_server(server, new, NULL);
}

static inline client_t *add_client_to_server_at_tail(server_t *server, client_t *new)
{
	return add_client_to_server(server, new, server->clients ? sever->clients->prev : NULL);
}

int client_in_server(server_t *server, client_t *client);

client_t *del_client_from_server(server_t *server, client_t *old);

static inline int get_num_clients(server_t *server)
{
        return server ? server->num_clients : -1;
}

/*
 * return value 1 empty , 0 not empty, -1 error
 */
static inline int is_empty_server(server_t *server)
{
	return server ? server->num_clients == 0 : -1;
}

int create_listen_socket_server_tcp(server_t *server);

client_t *accept_connect_from_client_tcp(server_t *server);

ssize_t recv_data_from_client_tcp(client_t *client, char *data, size_t len);
ssize_t send_data_to_client_tcp(client_t *client, char *data, size_t len);




#endif
