/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                CLIENT TCP
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include "request/request.h"
#include "socket.h"


int main(int argc, char *argv[]) {

  uint8_t online = 0;

  char request[MAX_BUFFER] = {0};
  char response[MAX_BUFFER] = {0};

  int client_socket = socket_create();

  socket_connect(client_socket, "127.0.0.1", 90190);

  socket_send(client_socket, request, request_driver(request, &online));

  socket_recieve(client_socket, response, MAX_BUFFER);

  printf("Server Response : %s\n\n",response);

  close(client_socket);
  return 0;
}
