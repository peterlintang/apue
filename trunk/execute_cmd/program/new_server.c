
/*
 * we implements the server again , thsi time we use new interfaces
 */

#include <stdio.h>
#include <stdlib.h>
#include "server.h"
#include "client.h"

int main(int argc, char **argv)
{
	client_t *client = NULL;
	server_t *server = NULL;


	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	server = new_server("wow", AF_INET, SERVER_PORT, IP_STR, BACKLOG);
	if (!server) {
		fprintf(stderr, "%s: create new server failed\n", __func__);
		exit(1);
	}

	if (create_listen_socket(server) == 1) {
		fprintf(stdout, "%s: create listen socket OK\n", __func__);
	} else {
		fprintf(stderr, "%s: create listen socket failed\n", __func__);
		destroy_server(&server);
		exit(2);
	}

	get_user_cmd_send_to_client_print_result(stdin, stdout, server, -1, 0);

	destroy_server(&server);
	
	return 0;

}
