/*-------------------------------------------------------------------------------------------------------SERVER CONNECTION
Dealing with Server connection(s).                                                                                             
------------------------------------------------------------------------------------------------------------------------*/
#include <stdlib.h>
#include "connection.h"

static void server_create(serv_t *server) {
/*creates a socket for two-way communication.*/

  System_Message("Creating socket");

  server->server_sock_desc = socket(AF_INET, SOCK_STREAM, 0);
  if (server->server_sock_desc < 0) {
    System_Message("Failed to create socket.");
    exit(EXIT_FAILURE);
  }//server failed to create a socket.

  return;
}

static void server_binder(serv_t *server, const char *ADDRESS, const char *PORT_STR) {
/*Binds server's ip to the socket.*/

  System_Message("Binding server to socket.");

  uint32_t PORT = atoi(PORT_STR);

  server->server_address.sin_addr.s_addr = inet_addr(ADDRESS);
  server->server_address.sin_family = AF_INET;
  server->server_address.sin_port = htons(PORT);
  
  int32_t bind_sock = bind(
    server->server_sock_desc, (struct sockaddr *) &server->server_address, sizeof(server->server_address));

  if (bind_sock < 0) {
    System_Message("Failed to bind socket.");
    exit(EXIT_FAILURE);
  }//server failed to bind socket.

  return;
}

void server_connect(serv_t *client, const char *ADDRESS, const char *PORT_STR) {
/*Wraps the previous static functions. If nothing fails the server's up and running.*/

  server_create(client);
  server_binder(client, ADDRESS, PORT_STR);

  System_Message("Server's up and running!");

  return;
}

void socket_listen(serv_t *server, uint16_t *status, uint16_t *error) {
/*Listens for incomming connections.*/

  int32_t list_sock = listen(server->server_sock_desc, MCONN);
  if (list_sock < 0) {
    *status |= (1 << ERROR); *error |= (1 << CLERR);
  }//server failed listening for clients.

  return;
}

void socket_accept(serv_t *server, uint16_t *status, uint16_t *error) {
/*Accepting incoming connection.*/

  Render_Header("IDLE", "Waiting for incoming connections");

  int32_t client_length = sizeof(server->client_address);

  server->client_sock_desc = accept(
  server->server_sock_desc, (struct sockaddr *) &server->client_address, (socklen_t*) &client_length);

  if (server->client_sock_desc < 0) {
    *status |= (1 << ERROR); *error |= (1 << CAERR);
    return;
  }//server failed accepting client.

  printf("\t\t\tClient connected at IP: %s and port: %i\n", 
    inet_ntoa(server->client_address.sin_addr),
    ntohs(server->client_address.sin_port)
  );
  
  return;
}