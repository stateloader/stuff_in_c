#include "socket.h"
#include "receive.h"
#include "writer.h"
#include "reader.h"

static int8_t database_action(server_t *server) {
  Message_Info("inside database_action");

  if (server->protocol[ABYTE] & (1 << RWBIT)) {
    Message_Info("writing to database");
    return database_writer(server);
  } else {
    Message_Info("reading from database");
    return database_reader(server);
  }
}

int8_t receive_driver(server_t *server) {
  Message_Info("inside receive driver");

  int8_t result = 0;
  server->size_pack = recv(server->conn.sock_clnt, server->pack, SBUFF, 0);
  result = protocol_append(server->pack, server->size_pack, server->protocol);
  if (result == FAIL) return result;

  

  return database_action(server);
}