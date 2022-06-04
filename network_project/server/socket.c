#include <sys/socket.h>
#include <arpa/inet.h>
#include "socket.h"

int socket_create(void) {
  printf("Create the socket\n");
  return socket(AF_INET, SOCK_STREAM, 0);
}

int socket_bind(int server_socket, char *address, int port) {

  struct sockaddr_in server_address = {0};
  
  server_address.sin_addr.s_addr = inet_addr(address);
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);

  return bind(server_socket, (struct sockaddr *) &server_address, sizeof(struct sockaddr_in)); 
}
/*
int socket_accept(int server_socket, struct sockaddr_in client_address) {
  printf("Waiting for incoming connections...\n");
  //struct sockaddr_in client_address = {0};
  int clientLen = sizeof(struct sockaddr_in);
  return accept(server_socket, (struct sockaddr *) &client_address, (socklen_t*) &clientLen);
}
*/
void socket_close(int client_socket) {
  close(client_socket);
  shutdown(client_socket, 0);
  shutdown(client_socket, 1);
  shutdown(client_socket, 2);
}