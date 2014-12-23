/*
 * head file for simple file server's client
 */

#ifndef _SIMPLE_FILE_SERVER_CLIENT_H
#define _SIMPLE_FILE_SERVER_CLIENT_H

#include "common_addr.h"


typedef struct __client_t {
	char 	*client_name;

	char	*file_name;
	int	connect_fd;

#define SFS_REPLACE	 1
#define SFS_REPLACE_MASK 0x00000001
	int	flags;

	server_addr_t	*server_addr;
	client_addr_t	*client_addr;

	struct __client_t *next; 	/* not used now */
	struct __client_t *prev;	/* not used now */
} client_t;

client_t *new_client(const char *client_name, const char *file_name);

void destroy_client(client_t **ppclient);

int connect_to_server_tcp(client_t *pclient);

ssize_t send_data_to_server_tcp(client_t *pclient, char *data, size_t len);
ssize_t recv_data_from_server_tcp(client_t *pclient, char *data, size_t len);

static inline char *get_client_name(client_t *pclient)
{
	if (pclient && pclient->client_name)
		return pclient->client_name;
	return NULL;
}

static inline char *set_client_name(client_t *pclient, const char *new_name)
{
	if (pclient) {

		char *tmp = NULL;

		if (pclient->client_name)
			tmp = pclient->client_name;
		if ((pclient->client_name = strdup(new_name))) 
			free(tmp);
		else 
			pclient->client_name = tmp;

		return pclient->client_name;
	}

	return NULL;
}

static inline char *get_client_file_name(client_t *pclient)
{
	if (pclient)
		return pclient->file_name;

	return NULL;
}

static inline char *set_client_file_name(client_t *pclient, const char *new_name)
{
	if (pclient) {

		char *tmp = NULL;

		if (pclient->file_name)
			tmp = pclient->file_name;
		if ((pclient->file_name = strdup(new_name)))
			free(tmp);
		else
			pclient->file_name = tmp;

		return pclient->file_name;
	}

	return NULL;
}

static inline server_addr_t *get_client_server_addr(client_t *pclient)
{
	if (pclient) return pclient->server_addr;

	return NULL;
}

/*
 * return 0 means success, < 0 means fail.
 */
static inline int set_client_server_addr(client_t *pclient, const int af,
		const uint16_t port, const char *ipstr, unsigned int flags)
{
	if (pclient)
		return set_server_addr(pclient->server_addr, af, port, ipstr, flags);

	return -3;
}

static inline client_addr_t *get_client_client_addr(client_t *pclient)
{
	if (pclient) return pclient->client_addr;

	return NULL;
}

static inline int set_client_client_addr(client_t *pclient, const int af,
		const uint16_t port, const char *ipstr, unsigned int flags)
{
	if (pclient)
		return set_client_addr(pclient->client_addr, af, port, ipstr, flags);

	return -3;
}

static inline ssize_t send_client_name_to_server(client_t *pclient)
{
	if (pclient && pclient->client_name) {
		return send_data_to_server_tcp(pclient, 
				pclient->client_name, strlen(pclient->client_name));
	}

	return -1;
}

static inline ssize_t send_client_file_name_to_server(client_t *pclient)
{
	if (pclient && pclient->file_name) {
		return send_data_to_server_tcp(pclient,
				pclient->file_name, strlen(pclient->file_name));
	}

	return -1;
}

#endif // _SIMPLE_FILE_SERVER_CLIENT_H
