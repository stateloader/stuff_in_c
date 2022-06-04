/*------------------------------------------------------------------------------------------------------------------------
SERVER HEADER
------------------------------------------------------------------------------------------------------------------------*/

#ifndef SERVER_H_
#define SERVER_H_
/*
#include <stddef.h>
#include <stdint.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define SOCK 0
#define BIND 1
#define LIST 2
#define RECV 3
#define EXIT 4

#define MAX_CLIENT 8

typedef struct Session {
  size_t client_count;
  int client_size;
} sess_t;

typedef struct Server {
  uint8_t state;
  sess_t session;
  int server_socket;
  int client_socket;
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;
} serv_t;
*/
void server_session(void);
//serv_t setup_connection(char *address, int port);

#endif




/*
static void init_portip(char *address, int port, serv_t *server) {

  int res = 0;
  res = server->server_address.sin_family = AF_INET;
  printf("sin_family\t\t\t\t: %d\n", res);

  res = server->server_address.sin_port = htons(port);
  printf("sin_port\t\t\t\t\t: %d\n", res);

  res = server->server_address.sin_addr.s_addr = inet_addr(address);
  printf("s_addr\t\t\t\t: %d\n", res);

  printf("address and port established\n");
}

static void init_socket(serv_t *server) {

  int res = 0;
  res = server->server_socket = socket(AF_INET, SOCK_STREAM, 0);

  printf("server_socket\t\t\t\t: %d\n", res);

  if (server->server_socket < 0) {
    printf("failed to create socket.\nterminating.\n\n");
    exit(EXIT_FAILURE);
  }
  printf("socket created.\n");
  server->state |= (1 << SOCK);
}

static void init_bind(serv_t *server) {

  if (bind(
			server->server_socket, (struct sockaddr *)&server->server_address, sizeof(server->server_address)) < 0)
	{
		printf("failed to bind socket.\nterminating.\n\n");
		exit(EXIT_FAILURE);
  }

  printf("socket binded.\n");
  server->state |= (1 << BIND);
}

static void init_listen(serv_t *server) {

  if (listen(server->server_socket, 5) < 0) {
    printf("failed to listen.\nterminating.\n\n");
    exit(EXIT_FAILURE);
  }
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
  server->client_socket = accept(server->server_socket, (struct sockaddr*)&server->client_address, &client_size);

	if (server->client_socket < 0) {
		printf("can't accept\n");
    exit(EXIT_FAILURE);
  }

	server->session.client_count += 1;
	printf("Client connected at IP: %s and port: %i",inet_ntoa(server->client_address.sin_addr),ntohs(server->client_address.sin_port));
}
*/
//void server_session(serv_t *server) {
/*
  int counter = 0;
  char client_incoming[MAX_BUFFER];
  char server_outgoing[MAX_BUFFER];

  char *teststring = "tillbaka-kaka\n";

  init_listen(server);
  printf("\nwaiting for connections...\n");

	while(1) {

    printf("counter\t\t\t\t\t: %d\n", counter);
    memset(client_incoming, '\0', MAX_BUFFER);
    memset(server_outgoing, '\0', MAX_BUFFER);

    accept_connection(server);

	  if (recv(server->client_socket, client_incoming, sizeof(client_incoming), 0) < 0) {
	    printf("couldn't recieve client message. terminating.");
	    exit(EXIT_FAILURE);
	  }
    printf("client wrote: %s\n\n", client_incoming);
    strcpy(server_outgoing, teststring);

	  if (send(server->client_socket, server_outgoing, strlen(server_outgoing), 0) < 0) {
	    printf("couldn't send server  message. terminating.");
	    exit(EXIT_FAILURE);
	  }
    counter++;
	  close(server->client_socket);
  }
  close(server->server_socket);
*/
