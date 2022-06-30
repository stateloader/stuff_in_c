#include <string.h>
#include "sstring.h"
#include "socket.h"
#include "response.h"

int8_t response_driver(server_t *server) {

  uint32_t size_send = send(server->conn.sock_clnt, server->resp, server->size_resp, 0);

  buffer_flush(server->pack, SBUFF);
  buffer_flush(server->resp, SBUFF);

  return response_driver_check(size_send, server->size_resp);
}
  