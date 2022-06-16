/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                CLIENT TCP
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include <stdlib.h>

#include "request/request.h"
#include "request/client.h"

static const char *GENERAL = \
  "Jacke Packe Koda Satan\n\n"
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore.\n"\
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore.\n"\
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore.\n";

int main(void) {

  Render_Header("CLIENT", GENERAL);

  client_t client = {.online = 0};
  if (request_driver(&client) != FLEE) {
    System_Message("Success request_driver");
    char byte = client.rqst[client.size_rqst - 2];
    PrintByte(byte);
    System_Message(client.rqst);
  } else {
    System_Message("Error in request_driver, FLEE");
    exit(EXIT_FAILURE);
  }

 exit(EXIT_SUCCESS);
}

/*
  int client_socket = socket_create();
  socket_connect(client_socket, "127.0.0.1", 90190);

  if (request_driver(&client) != FLEE) {
    socket_send(client_socket, client.rqst, client.size_rqst);
    socket_recieve(client_socket, client.resp, RBUFF);
  } else {
    close(client_socket);
    exit(EXIT_FAILURE);
  }
  close(client_socket);
  exit(EXIT_SUCCESS);
  */