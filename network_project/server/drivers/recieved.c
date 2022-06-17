/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                  RECIEVED
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include <sys/socket.h>
#include "database.h"
#include "recieved.h"

//static uint8_t endbytes[] = {RULON, RUSUP, RDTMP, RDMSG, RARED, RABLU, RAGRN, RWMSG};

int8_t recieved_driver(server_t *server) {

  System_Message("Inside recieved_driver");
  server->size_recv = recv(server->session.sock_clnt, server->recv, SBUFF, 0);

  if (!recieved_check(server))
    return FAIL;
  else
    return database_driver(server);
    
  System_Message("outside recieved_driver ststament without a returncall.");
  return FAIL;
}
