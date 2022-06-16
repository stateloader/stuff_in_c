/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    CLIENT
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include <stdlib.h>
#include "socket.h"
#include "request/request.h"
#include "request/client.h"

static const char *GENERAL = \
  "Jacke Packe CLIENT\n\n"
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore.\n"\
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore.\n"\
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore.\n";

int main(void) {

  Render_Header("CLIENT", GENERAL);
  int client_socket = socket_create();
  socket_connect(client_socket, "127.0.0.1", 90190);

  client_t client = {.online = 0};

  if (request_driver(&client) != FLEE) {
    printf("ja jag e har\n");
    socket_send(client_socket, client.rqst, client.size_rqst);
    socket_recieve(client_socket, client.resp, RBUFF);
    printf("tillbaka: %s\n", client.resp);
  } else {
    close(client_socket);
    exit(EXIT_FAILURE);
  }
  close(client_socket);
  exit(EXIT_SUCCESS);
}