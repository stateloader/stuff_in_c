#include "socket.h"
#include "receive.h"
#include "writer.h"
#include "reader.h"

static int8_t database_action(server_t *server) {
  System_Message("inside database_action");

  if (server->protocol[EINDX] & (1 << RWBIT)) {
    System_Message("writing to database");
    return database_writer(server);
  } else {
    System_Message("reading from database");
    return database_reader(server);
  }
}

int8_t receive_driver(server_t *server) {
  System_Message("inside receive driver");

  int8_t result = 0;
  server->size_pack = recv(server->conn.sock_clnt, server->pack, SBUFF, 0);
  
  result = protocol_append(server->pack, server->size_pack, server->protocol);
  if (result == FAIL) return result;
  return database_action(server);
}