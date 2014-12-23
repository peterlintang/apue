
/*
 * wow implements the server
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "server.h"


int main(int argc, char **argv)
{
	client_t *client = NULL;
	server_t *server = NULL;
			
	server = new_server("ouch", AF_INET, 
			SERVER_PORT, IP_STR, 
			BACKLOG);
	if (!server) {
		fprintf(stderr, "%s: create new server error\n", __func__);
		exit(1);
	}

	if (create_listen_socket(server)) {
		fprintf(stdout, "create listen socket OK\n");
	} else {
		fprintf(stderr, "%s: create listen socket error\n", __func__);
		destroy_server(&server);
		exit(2);
	}

	if ((client = accept_connect_from_client(server)) != NULL) {
		fprintf(stdout, "adding one client to server...\t");
		add_client_to_server(server, client, NULL);
		fprintf(stdout, "%s: %d hdsdfsd\n", __func__, sizeof("hello guy\n"));
		fprintf(stdout, "send mesg %d\n", send_mesg_to_client_tcp(client, "hello guy\n", 11));
		fprintf(stdout, "add done\n");
	} else {
		fprintf(stderr, "accept client failed\n");
		destroy_server(&server);
	}

	if ((client = accept_connect_from_client(server)) != NULL) {
		fprintf(stdout, "adding one client to server...\t");
		add_client_to_server(server, client, NULL);
		fprintf(stdout, "send mesg %d\n", send_mesg_to_client_tcp(client, "hello guy hehehe we can communicate now\n", 40));
		fprintf(stdout, "add done\n");
	} else {
		fprintf(stderr, "accept client failed\n");
		destroy_server(&server);
	}

	if ((client = accept_connect_from_client(server)) != NULL) {
		fprintf(stdout, "adding one client to server...\t");
		add_client_to_server(server, client, NULL);
		fprintf(stdout, "add done\n");
		fprintf(stdout, "%s: sending cmd to client...\n", __func__);
		send_cmd_to_client(stdin, stdout, client);
		fprintf(stdout, "%s: send cmd OK\n", __func__);
	} else {
		fprintf(stderr, "accept client failed\n");
		destroy_server(&server);
	}

	fprintf(stdout, "%s: showing clients info...\n", __func__);
	show_clients_info(server);
	fprintf(stdout, "%s: done\n", __func__);
	sleep(5);
	destroy_server(&server);
	exit(0);
}
