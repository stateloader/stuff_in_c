#include "receive.h"
#include "writer.h"
#include "reader.h"
#include "socket.h"

static int8_t protocol_append(server_t *server) {
  System_Message("inside protocol append");

  server->protocol[TINDX] = server->recv[server->size_recv - 4];
  server->protocol[EINDX] = server->recv[server->size_recv - 3];
  server->protocol[FINDX] = server->recv[server->size_recv - 2];
  return SUCC;
}

static int8_t protocol_rwbill(server_t *server) {
  System_Message("inside protocol rwbill");

  if (server->protocol[EINDX] & (1 << RWBIT)) {
    System_Message("writing to database");
    write_driver(server);
  } else {
    System_Message("reading from database");
    read_driver(server);
  }
  return SUCC;
}

int8_t receive_driver(server_t *server) {
  System_Message("receive driver");

  server->size_recv = recv(server->conn.sock_clnt, server->recv, SBUFF, 0);
  protocol_append(server);
  protocol_rwbill(server);

  return SUCC;
}