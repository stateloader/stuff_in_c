/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                  RESPONSE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include <sys/socket.h>
#include "drivers/database/database.h"
#include "drivers/sconfig.h"
#include "drivers/incoming.h"
#include "drivers/encoding.h"
#include "drivers/outgoing.h"
#include "server.h"
#include "response.h"

static int8_t response_incoming(server_t *server) {
  //recv(client_socket, request, SBUFF, 0);
  return SUCC;
}

static int8_t response_encoding(server_t *server) {
  return SUCC;
}

static int8_t response_outgoing(server_t *server) {
  //send(client_socket, response, strlen(response), 0);
  return SUCC;
}

int8_t response_driver(server_t *server) {
  incoming(server);
  outgoing(server);
  return SUCC;
}
