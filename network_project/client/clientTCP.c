/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                CLIENT TCP
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include "utils.h"
#include "request.h"
#include "socket.h"

int main(int argc, char *argv[]) {

  char request[MAX_BUFFER] = {0};
  char response[MAX_BUFFER] = {0};

  int client_socket = socket_create();
  socket_connect(client_socket, "127.0.0.1", 90190);

  int request_size = request_driver(request);
  socket_send(client_socket, request, request_size);

  int response_size = socket_recieve(client_socket, response, MAX_BUFFER);
  printf("Server Response : %s\n\n",response);

  socket_close(client_socket);
  return 0;
}
