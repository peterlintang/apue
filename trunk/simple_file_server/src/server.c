/*
 * implement the server functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "server.h"
#include "client.h"

server_t *new_server(const char *server_name, unsigned int back_log,
		const int at, const uint16_t port, const char *ipstr)
{
	server_t *server = calloc(1, sizeof(*server));
	if (!server) return server;

	if (server_name && (server->server_name = strdup(server_name))
		&& (server->server_addr = new_server_addr(af, port, ipstr)))
		server->back_log = (back_log == 0 ? MAX_BACKLOG : backlog);
		server->listen_fd = -1;
	else 
		destroy_server(&server);

	return server;
}

void destroy_server(server_t **ppserver)
{
		// wait to finish
}

char *get_server_name(server_t *pserver)
{
        if (pserver && pserver->server_name)
                return pserver->server_name;
        return NULL;
}

char *set_server_name(server_t *pserver, const char *new_name)
{
        if (pserver) {

                char *tmp = NULL;

                if (pserver->server_name)
                        tmp = pserver->server_name;
                if ((pserver->server_name = strdup(new_name)))
                        free(tmp);
                else
                        pserver->server_name = tmp;

                return pserver->server_name;
        }

        return NULL;
}

unsigned int get_server_backlog(server_t *server)
{
	if (server) return server->back_log;

	return 0;	/* right ??? */
}

unsigned int set_server_backlog(server_t *server, unsigned int new)
{
	int ret;

	if (!server) return 0;

	ret = server->back_log;
	server->back_log = new;

	return ret;
}

client_t *add_client_to_server(server_t *server, client_t *new, client_t *after)
{
	if (!new || !server || (!server->clients && after)) return NULL;

	if (!server->clients) {
		server->clients = new;
		new->prev  = new;
		new->after = new;
	} else if (!after) {
		new->next 	= server->clients;
		server->clients->prev->next = new;
		new->prev	= server->clients->prev;
		server->clients->prev = new;

		server->clients = new;
	} else {
		new->next = after->next;
		after->next->prev = new;
		after->next = new;
		new->prev = after;
	}

	server->num_clients++;
	return new;
}

int client_in_server(server_t *server, client_t *client)
{
	int i;
	client_t *tmp;

	if (!server || !client) return -1;  // error

	for (i = 0, tmp = server->clients; i < server->num_clients; i++, tmp = tmp->next)
		if (client == tmp) return 1;	// foudn

	return 0;	// not found
}

client_t *del_client_from_server(server_t *server, client_t *old)
{
	if (!server || !server->clients || 
		!old || !client_in_server(server, old)) 
		return NULL;

//	if (client_in_server(server, old) != 1) return NULL;	// old is not in the server's clients list

	if (server->num_clients == 1) {
		server->clients = NULL;
	} else if (old == server->clients) {
		server->clients = old->next;
	}

	old->prev->next = old->next;
	old->next->prev = old->prev;
	old->next = NULL;
	old->prev = NULL;

	server->num_clients--;
	return old;
}

int create_listen_socket_server_tcp(server_t *server)
{
	struct sockaddr_in	server_addr;

	if (!server)	return -1;

	server->listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server->listen_fd < 0)	return -1;

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family 	= server->server_addr->af;
	server_add.sin_port	= htons(server->server_addr->port);
	inet_pton(server->server_addr->af, &server_addr.sin_addr, 
			server->server_addr->ipstr);

	if (bind(server->listen_fd, (struct sockaddr *)&server_addr, 
		sizeof(server_addr)) < 0) return -1;

	if (listen(server->listen_fd, server->back_log)) {
		server->listen_fd = -1;
		return -1;
	}

	return 0;
}

client_t *accept_connect_from_client_tcp(server_t *server)
{
	char	*file_name = NULL;;
	char	*client_name = NULL;
	char	ipstr[256];
	int	file_name_len;
	int	client_name_len;
	int	connectfd;
	int	len;
	struct  sockaddr_in	clientaddr;
	client_t	*client = NULL;

	if (!server || !server->server_addr || server->listen_fd == -1)
		return NULL;

	len = sizeof(clientaddr);
	connectfd = accept(server->listen_fd, 
		(struct sockaddr *)&clientaddr, &len);
	if (connectfd < 0) {
		return NULL;
	}

	/* here should get the filename & client name from client */
	if (read(connectfd, &len, sizeof(int)) > 0) {
		client_name = malloc(len + 1);
		memset(client_name, 0, len + 1);
		if (read(connectfd, client_name, len) > 0)
			client_name[len] = '\0';
	}

	if (read(connectfd, &len, sizeof(int)) > 0) {
		file_name = malloc(len + 1);
		memset(file_name, 0, len + 1);
		if (read(connectfd, file_name, len) > 0)
			file_name[len] = '\0';
	}

	client = new_client(client_name, file_name);
	if (!client) {
		close(connectfd);
		return NULL;
	}

	client->connect_fd = connectfd;

	inet_ntop(clientaddr.sin_family, &clientaddr.sin_addr, ipstr, 200);
	client->client_addr = new_client_addr(clientaddr.sin_family, 
				ntohs(clientaddr.sin_port, ipstr));

	return client;
}























