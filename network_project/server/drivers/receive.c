#include "socket.h"
#include "validate.h"
#include "receive.h"
#include "writer.h"
#include "reader.h"

static int8_t database_driver(server_t *server) {
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

  server->size_pack = recv(server->conn.sock_clnt, server->pack, SBUFF, 0);

  send(server->conn.sock_clnt, server->pack, server->size_pack, 0);
  /*
  int8_t result = protocol_append(server->pack, server->size_pack, server->protocol);
  if (result == FAIL)return result;

  if (server->protocol[SBYTE] & (0 << VALID))
    return validate_driver(server);
  else
    return database_driver(server);
  */
   return SUCC;
}