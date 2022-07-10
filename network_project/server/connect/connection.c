/*-------------------------------------------------------------------------------------------------------SERVER CONNECTION
                                                                                                            
------------------------------------------------------------------------------------------------------------------------*/

#include "connection.h"

static const char *ADDRESS = "127.0.0.1";
static const int32_t PORT = 90190;

void server_create(serv_t *server, uint16_t *status, uint16_t *error) {
/*creates a socket for two-way communication.*/

  System_Message("Creating socket");

  server->server_sock_desc = socket(AF_INET, SOCK_STREAM, 0);
  if (server->server_sock_desc < 0) {
    *status |= (1 << ERROR); *error |= (1 << SSERR);
  }// Server failed to create a socket.
  return;
}

void server_binder(serv_t *server, uint16_t *status, uint16_t *error) {
/*Binds server's ip to the socket.*/

  System_Message("Binding server's address to socket.");

  server->server_address.sin_addr.s_addr = inet_addr(ADDRESS);
  server->server_address.sin_family = AF_INET;
  server->server_address.sin_port = htons(PORT);
  
  int32_t bind_sock = bind(
    server->server_sock_desc, (struct sockaddr *) &server->server_address, sizeof(server->server_address));

  if (bind_sock < 0) {
    *status |= (1 << ERROR); *error |= (1 << SCERR);
  }// Server failed binding address to socket.
  *status |= (1 << ALIVE);
  return;
}
void socket_listen(serv_t *server, uint16_t *status, uint16_t *error) {
/*Listens for incomming connections.*/

  int32_t list_sock = listen(server->server_sock_desc, MCONN);
  if (list_sock < 0) {
    *status |= (1 << ERROR); *error |= (1 << CLERR);
  }// Server failed listening for clients.
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
  }// Server failed accepting client.

  printf("\t\t\tClient connected at IP: %s and port: %i\n", 
    inet_ntoa(server->client_address.sin_addr),
    ntohs(server->client_address.sin_port)
  );
  return;
}