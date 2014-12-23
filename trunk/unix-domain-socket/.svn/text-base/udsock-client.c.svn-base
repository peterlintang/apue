
/*
 * implements the unix domain sock client interfaces
 * filename:	udsock-client.c
 */

#include "udsock-client.h"

unix_sock_client *create_unix_sock_client(const char *pathname)
{
	unix_sock_client 	*client = NULL;

	if (!pathname) {
		fprintf(stderr, "arguments error, path: %s\n",
				pathname);
		return NULL;
	}

	if (!(client = calloc(1, sizeof(*client)))) {
		fprintf(stderr, "can not allocate memory for client\n");
		return NULL;
	}

	if (!(client->path = strdup(pathname))) {
		fprintf(stderr, "can dup pathname\n");
		free(client);
		return NULL;
	}

/*
*/

	client->conn_sock = -1;
	fprintf(stdout, "create client: %s, conn sock: %d\n",
			client->path, client->conn_sock);
	return client;
}

void destroy_unix_sock_client(unix_sock_client **ppclient)
{
	unix_sock_client *client = NULL;

	if (ppclient && (client = *ppclient)) {
		fprintf(stdout, "destroy client: %s, conn sock: %d\n",
				client->path, client->conn_sock);
		if (client->conn_sock != -1)
			close(client->conn_sock);
		free(client->path);
		free(client);
		*ppclient = NULL;
	}
}

int unix_sock_connect(unix_sock_client *client)
{
//;	struct sockaddr_un addr;
	struct sockaddr_un addr;

	if (!client) {
		fprintf(stderr, "arguments error\n");
		return -3;
	}

	if ((client->conn_sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr, "can not create unix domain socket\n");
		perror("socket");
		return -2;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	sprintf(addr.sun_path, "%s", client->path);

	if (connect(client->conn_sock, 
		(const struct sockaddr *)&addr, sizeof(addr)) < 0) {
		fprintf(stderr, "can not connect to server: %s\n",
			client->path);
		close(client->conn_sock);
		client->conn_sock = -1;
		return -1;
	}

	fprintf(stdout, "connect to server: %s success\n", client->path);

	return 0;
}

int unix_sock_send_client(unix_sock_client *client, 
				char *buf, unsigned int len)
{
	int		total 		= 0;
//	uint32_t	bytes_send 	= htonl(len);	// doesnot need this, since is on the same machine
	uint32_t	bytes_send 	= len;
	int		send_len 	= 0;

	if (!client || !buf) {
		fprintf(stderr, "arguments error\n");
		return -2;
	}

	fprintf(stdout, "sending %d bytes...\n", len);

	if ((total = write(client->conn_sock, 
			&bytes_send, sizeof(uint32_t))) == -1) {
		fprintf(stderr, "send data head error, host: %d, net: %d\n",
				len, bytes_send);
		return -1;
	}

	total = 0;
	while (total < len) {
		send_len = write(client->conn_sock, buf + total, len - total);
//		if (send_len == -1) {
		if (send_len <= 0) {
			if (errno == EINTR)
//				break;
				continue;
			else {
				perror("write");
				return -1;
			}
		}

//		if (send_len == 0) break; // write return zero means what ??
					  // treat it as an error ???

		total += send_len;
		fprintf(stdout, "send_len: %d, total: %d\n", send_len, total);
	}

	fprintf(stdout, "send %d bytes\n", total);

	return total;
}


int unix_sock_recv_client(unix_sock_client *client, 
				char *buf, unsigned int len)
{
	int	 total 		= 0;
	int	 recv_len	= 0;
	uint32_t bytes_recv	= 0;

	if (!client || !buf) {
		fprintf(stderr, "arguments error\n");
		return -2;
	}

	if ((recv_len = read(client->conn_sock, 
			&bytes_recv, sizeof(uint32_t))) == -1) {
		fprintf(stderr, "read header from server error\n");
		return -1;
	}

//	recv_len = ntohl(bytes_recv); // doesnot need this since on the same machine
	recv_len = bytes_recv;

	fprintf(stdout, "receiving %d bytes...\n", recv_len);

	if (recv_len > len) {
		fprintf(stderr, "data(bytes: %d) too large for the buf(bytes: %d) to store\n",
			recv_len, len);
		return -3;
	}

	while (total < recv_len) {
		len = read(client->conn_sock, buf + total, recv_len - total);
		if (len == -1) {
			if (errno == EINTR)
				continue;
			else {
				perror("read");
				return -1;
			}
		}
		if (len == 0) break;
		total += len;
		fprintf(stdout, "len: %d, total: %d\n", len, total);
	}

	fprintf(stdout, "read %d bytes from server\n", total);

	return total;
}







