/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                CLIENT TCP
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include "utils.h"
#include "command.h"
#include "socket.h"

int main(int argc, char *argv[]) {

  char *address = "127.0.0.1";
  int port = 90190;

  int client_socket = 0;
  size_t request_size = 0;
  size_t response_size = 0;

  char request[MAX_BUFFER] = {0};
  char response[MAX_BUFFER] = {0};

  client_socket = socket_create();
  socket_connect(client_socket, address, port);

  request_size = command_driver(request);
  socket_send(client_socket, request, request_size);
  
  response_size = socket_recieve(client_socket, response, MAX_BUFFER);
  
  printf("Server Response : %s\n\n",response);
  socket_close(client_socket);
  return 0;
}
