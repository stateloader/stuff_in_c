#include "receiver.h"
#include "writer.h"
#include "reader.h"
#include "socket.h"

static void protocol_append(server_t *server) {
  System_Message("inside protocol append");

  server->protocol[TINDX] = server->recv[server->size_recv - 4];
  server->protocol[EINDX] = server->recv[server->size_recv - 3];
  server->protocol[FINDX] = server->recv[server->size_recv - 2];

  PrintByte(server->protocol[TINDX]);
  PrintByte(server->protocol[EINDX]);
  PrintByte(server->protocol[FINDX]);

  return;
}

static void protocol_rwbill(server_t *server) {
  System_Message("inside protocol rwbill");

  if (server->protocol[EINDX] & (1 << RWBIT)) {
    System_Message("writing to Database");
    write_driver(server);
  } else {
    System_Message("reading from Database");
    read_driver(server);
  }
}

void receive_driver(server_t *server) {
  System_Message("receive driver");

  server->size_recv = recv(server->conn.sock_clnt, server->recv, SBUFF, 0);
  protocol_append(server);
  protocol_rwbill(server);
}