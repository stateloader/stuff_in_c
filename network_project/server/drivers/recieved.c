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
/*  
  data_t database = {.status = 1};
  database.size_recv = string_copy(database.recv, server->recv, SBUFF);

  fetch_endb(database.reqbyte, database.recv, database.size_recv);

  if (!recieved_driver_check(&database))
    return FAIL;

  else if (!database_driver(&database))
    return FAIL;
*/
  return SUCC;
}