#include "receiver.h"
#include "writer.h"
#include "reader.h"
#include "socket.h"

static void protocol_append(server_t *server) {
  server->protocol[TINDX] = server->recv[server->size_recv - 4];
  server->protocol[EINDX] = server->recv[server->size_recv - 3];
  server->protocol[FINDX] = server->recv[server->size_recv - 2];
  return;
}

static void protocol_rwbill(server_t *server) {

  if (server->protocol[EINDX] & (1 << RWBIT)) {
    System_Message("Reading from Database");
    write_driver(server);
  } else {
    System_Message("Writing to Database");
    read_driver(server);
  }
}
void receive_driver(server_t *server) {
  server->size_recv = recv(server->conn.sock_clnt, server->recv, SBUFF, 0);
  protocol_append(server);
  protocol_rwbill(server);
  System_Message(server->recv);
}