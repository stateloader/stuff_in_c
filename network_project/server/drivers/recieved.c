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

  if (!recieved_check(server))
    return FAIL;
  return database_driver(server);
    
  System_Message("outside recieved_driver ststament without a returncall.");
  return FAIL;
}
