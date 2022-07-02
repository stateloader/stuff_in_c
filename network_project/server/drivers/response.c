#include <string.h>
#include "sstring.h"
#include "socket.h"
#include "response.h"

static void server_reset(server_t *server) {
  buffer_flush(server->pack, SBUFF);
  buffer_flush(server->resp, SBUFF);
}

int8_t response_driver(server_t *server, int8_t control) {
  System_Message("Responding client");

  uint32_t size_send = send(server->conn.sock_clnt, server->resp, server->size_resp, 0);
  server_reset(server);

  return response_driver_check(size_send, server->size_resp);
}