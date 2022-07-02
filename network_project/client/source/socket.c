/*------------------------------------------------------------------------------------------------------------CLIENT SOCKET

------------------------------------------------------------------------------------------------------------------------*/

#include "socket.h"

int32_t socket_create(void) {
  System_Message("creating socket");
  return socket(AF_INET, SOCK_STREAM, 0);
}

int32_t socket_connect(int32_t client_socket, char *address, int32_t port) {
  System_Message("connecting to server");

  struct sockaddr_in server_address = {0};
  server_address.sin_addr.s_addr = inet_addr(address);
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);

  return connect(client_socket, (struct sockaddr *) &server_address, sizeof(struct sockaddr_in)); 
}