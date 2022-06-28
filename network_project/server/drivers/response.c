#include <string.h>
#include "sstring.h"
#include "socket.h"
#include "response.h"

int8_t response_driver(server_t *server) {
  Message_Info("inside respond_driver");

  uint32_t size_send = send(server->conn.sock_clnt, server->resp, server->size_resp, 0);
  return response_driver_check(size_send, server->size_resp);
}
