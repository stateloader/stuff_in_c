/*------------------------------------------------------------------------------------------------------------------------
                                                                                                             CLIENT MODULE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#include <sys/socket.h>
#include <arpa/inet.h>
#include "socket.h"

int socket_create(void) {
  
  int client_socket;
  
  printf("Create the socket\n");
  client_socket = socket(AF_INET, SOCK_STREAM, 0);
  
  return client_socket;
}

int socket_connect(int client_socket, char *address, int port) {

  int retval = -1;
  struct sockaddr_in server_address = {0};
  
  server_address.sin_addr.s_addr = inet_addr(address);
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);
  retval = connect(client_socket, (struct sockaddr *) &server_address, sizeof(struct sockaddr_in));
  
  return retval;
}

int socket_send(int client_socket, char* request, size_t request_size) {

  int retval = -1;
  retval = send(client_socket, request, request_size, 0);
  return retval;
}
//receive the data from the server
int socket_recieve(int client_socket, char* response, size_t response_size) {

    int retval = -1;
    retval = recv(client_socket, response, response_size, 0);
    printf("Response %s\n", response);
    return retval;
}