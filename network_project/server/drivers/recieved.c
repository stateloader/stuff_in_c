/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                  RECIEVED
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include <sys/socket.h>
#include "database.h"
#include "recieved.h"

int8_t recieved_driver(server_t *server) {
  System_Message("Inside recieved_driver");

  server->size_recv = recv(server->session.sock_clnt, server->recv, SBUFF, 0);

  printf("minus 4: ");
  PrintByte(server->recv[server->size_recv - 4]);
  printf("minus 3: ");
  PrintByte(server->recv[server->size_recv - 3]);
  printf("minus 2: ");
  PrintByte(server->recv[server->size_recv - 2]);
  System_Message(server->recv);
  return SUCC;
}