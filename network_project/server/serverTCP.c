/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                SERVER TCP
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "socket.h"
#include "response.h"

int main(void) {

  int server_socket = 0;
 // int client_length = 0;
  int client_socket = 0;

  struct sockaddr_in server_address;
  struct sockaddr_in client_address;

  char request[MAX_BUFFER] = {0};
  char response[MAX_BUFFER] = {0};

  socket_create(&server_socket);
  socket_bind(server_socket, &server_address, "127.0.0.1", 90190);
  socket_listen(server_socket);

  while(1) {

		socket_accept(server_socket, &client_socket, &client_address);
    response_driver(client_socket, request, response);
    close(client_socket);
  }
  return 0;
}
