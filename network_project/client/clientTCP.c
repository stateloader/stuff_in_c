/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                CLIENT TCP
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#include <unistd.h>
#include "socket.h"

int main(int argc, char *argv[]) {

  //int client_socket = 0;
  size_t request_size = 0;
  size_t response_size = 0;
  struct sockaddr_in server;

  char request[MAX_BUFFER] = {0};
  char response[MAX_BUFFER] = {0};

  client_socket = socket_create();
  socket_connect(client_socket);

  request_size = command_driver(request);
  socket_send(client_socket, request, request_size);
  
  response_size = socket_recieve(client_socket, response, MAX_BUFFER);
  
  printf("Server Response : %s\n\n",response);

  close(client_socket);
  shutdown(client_socket,0);
  shutdown(client_socket,1);
  shutdown(client_socket,2);
  return 0;
}
