/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                  RECIEVED
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include <sys/socket.h>
#include "database.h"
#include "recieved.h"

static uint8_t endbytes[] = {RULO, RUSU, RDTP, RDMG, RADR, RADB, RADG, RWMG};

int8_t recieved_driver(server_t *server) {

  server->size_recv = recv(server->session.sock_clnt, server->recv, SBUFF, 0);
  if (!recieved_check(server, endbytes))
    return FAIL;
  else
    return database_driver(server);
}
