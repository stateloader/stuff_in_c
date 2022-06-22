/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    SOCKET
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#include <sys/socket.h>
#include <arpa/inet.h>
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

int32_t socket_send(int32_t client_socket, char *request, int32_t request_size) {
  return send(client_socket, request, request_size, 0);
}

int32_t socket_recieve(int32_t client_socket, char *response, int32_t response_size) {
  return recv(client_socket, response, response_size, 0);
}
