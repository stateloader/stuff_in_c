/*------------------------------------------------------------------------------------------------------------------------
                                                                                                             SOCKET MODULE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#include <sys/socket.h>
#include <arpa/inet.h>
#include "socket.h"

int socket_create(void) {

  printf("Create the socket\n");
  return socket(AF_INET, SOCK_STREAM, 0);
}

int socket_connect(int client_socket, char *address, int port) {

  struct sockaddr_in server_address = {0};

  server_address.sin_addr.s_addr = inet_addr(address);
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);

  return connect(client_socket, (struct sockaddr *) &server_address, sizeof(struct sockaddr_in)); 
}

int socket_send(int client_socket, char *request, int request_size) {

  return send(client_socket, request, request_size, 0);
}

int socket_recieve(int client_socket, char *response, int response_size) {

  return recv(client_socket, response, response_size, 0);
}
