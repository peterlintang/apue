/*
 * implement the client functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "server.h"
#include "client.h"

client_t *new_client(const char *client_name, const char *file_name)
{
	client_t *client = calloc(1, sizeof(client_t));

	if (client) {
		client->client_name = strdup(client_name);
		client->file_name = strdup(file_name);
		client->connect_fd = -1;
	}

	return client;
}

void destroy_client(client_t **ppclient)
{
	if (ppclient && *ppclient) {
		free((*ppclient)->client_name);
		free((*ppclient)->file_name);
		destroy_server_addr(&((*ppclient)->server_addr));
		destroy_client_addr(&((*ppclient)->client_addr));
		if ((*ppclient)->connect_fd > 0) 
			close((*ppclient)->connect_fd);
	}
}

int connect_to_server_tcp(client_t *pclient)
{
	int	len;
	int	ret = 0;
	struct  sockaddr_in	serveraddr;

	pclient->connect_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (pclient->connect_fd == -1) ret = -1;

	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = pclient->server_addr->af;
	serveraddr.sin_port   = pclient->server_addr->port;
	inet_pton(pclient->server_addr->af, 
		pclient->server_addr->ipstr, &serveraddr.sin_addr);

	if (connect(pclient->connect_fd, 
		(struct sockaddr *) &serveraddr, sizeof(serveraddr)) == -1)
		ret = -1;

	len = strlen(pclient->client_name);
	send_data_to_server_tcp(pclient, (char *)&len, sizeof(len));
	send_data_to_server_tcp(pclient, pclient->client_name, len);

	len = strlen(pclient->file_name);
	send_data_to_server_tcp(pclient, (char *)&len, sizeof(len));
	send_data_to_server_tcp(pclient, pclient->file_name, len);

	return ret;
}

/*
 * should make sure @data has enough space to store data 
 */
ssize_t send_data_to_server_tcp(client_t *pclient, char *data, size_t len)
{
	unsigned int sendcount;

	if (!pclient || pclient->connect_fd < 0) return -1;

	if (!data) return -1;

	if (strlen(data) < len) len = strlen(data);

	sendcount = write(pclient->connect_fd, data, len);

	return sendcount;
}

/*
 * should make sure @data has enough space to store data 
 */
ssize_t recv_data_from_server_tcp(client_t *pclient, char *data, size_t len)
{
	int recvcount;
	int datalen = 0;

	if (!pclient || pclient->connect_fd < 0)
		return -1;

	if (!data) return -1;

	if ((datalen = strlen(data)) < len) len = datalen;

	recvcount = read(pclient->connect_fd, data, len);
//	data[recvcount] = '\0';

	return recvcount;
}

