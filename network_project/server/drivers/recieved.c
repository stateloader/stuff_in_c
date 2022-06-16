/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                  RECIEVED
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include <sys/socket.h>
#include "recieved.h"

int8_t recieved_driver(server_t *server) {
  server->size_recv = recv(server->session.sock_clnt, server->recv, SBUFF, 0);
  System_Message(server->recv);
  return recieved_check(server);
}
