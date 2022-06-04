/*------------------------------------------------------------------------------------------------------------------------
                                                                                                             SERVER MODULE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scan.h"
#include "server.h"

static void init_portip(char *address, int port, serv_t *server) {

  server->server_address.sin_family = AF_INET;
  server->server_address.sin_port = htons(port);
  server->server_address.sin_addr.s_addr = inet_addr(address);
  printf("address and port established\n");
}

static void init_socket(serv_t *server) {

  server->socket_server = socket(AF_INET, SOCK_STREAM, 0);

  if (server->socket_server < 0) {
    printf("failed to create socket.\nterminating.\n\n");
    exit(EXIT_FAILURE);
  }
  printf("socket created.\n");
  server->state |= (1 << SOCK);
}

static void init_bind(serv_t *server) {

  if (bind(
			server->socket_server, (struct sockaddr *)&server->server_address, sizeof(server->server_address)) < 0)
	{
		printf("failed to bind socket.\nterminating.\n\n");
		exit(EXIT_FAILURE);
  }

  printf("socket binded.\n");
  server->state |= (1 << BIND);
}

static void init_listen(serv_t *server) {

  if (listen(server->socket_server, 1) < 0) {
    printf("failed to listen.\nterminating.\n\n");
    exit(EXIT_FAILURE);
  }
  printf("\nwaiting for connections...\n");
  server->state |= (1 << LIST);

}

serv_t setup_connection(char *address, int port) {

  serv_t server = {.state = 0x00};

  init_portip(address, port, &server);

  init_socket(&server);
  init_bind(&server);
  init_listen(&server);

  return server;
}

void accept_connection(serv_t *server) {

  int client_size = sizeof(server->client_address);
  server->socket_client = accept(server->socket_server, (struct sockaddr*)&server->client_address, &client_size);

	if (server->socket_client < 0) {
		printf("can't accept\n");
    exit(EXIT_FAILURE);
  }

	server->session.client_count += 1;
//	server->session.client_size = client_size;

	printf("Client connected at IP: %s and port: %i",inet_ntoa(server->client_address.sin_addr),ntohs(server->client_address.sin_port));
}

void server_session(serv_t *server) {

  char client_incoming[MAX_BUFFER];
  char server_outgoing[MAX_BUFFER];

  char *teststring = "tillbaka-kaka\n";

  init_listen(server);

	while(1) {

    memset(client_incoming, '\0', MAX_BUFFER);
    memset(server_outgoing, '\0', MAX_BUFFER);

    accept_connection(server);

	  if (recv(server->socket_client, client_incoming, sizeof(client_incoming), 0) < 0) {
	    printf("couldn't recieve client message. terminating.");
	    exit(EXIT_FAILURE);
	  }
    printf("client wrote: %s\n\n", client_incoming);
    strcpy(server_outgoing, teststring);

	  if (send(server->socket_client, server_outgoing, strlen(server_outgoing), 0) < 0) {
	    printf("couldn't send server  message. terminating.");
	    exit(EXIT_FAILURE);
	  }
	  close(server->socket_client);
  }
  close(server->socket_server);
}
