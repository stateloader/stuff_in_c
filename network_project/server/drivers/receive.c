/*-----------------------------------------------------------------------------------------------------------------RECEIVE
                                                                                                            
------------------------------------------------------------------------------------------------------------------------*/
#include "socket.h"
#include "sstring.h"
#include "receive.h"
#include "writer.h"
#include "reader.h"

static int8_t database_driver(server_t *server) {

  if (server->protocol[ABYTE] & (1 << RWBIT))
    return database_writer(server);
  else
    return database_reader(server);
}

int8_t receive_driver(server_t *server) {

  server->size_pack = recv(server->conn.sock_clnt, server->pack, SBUFF, 0);
  System_Message("receiving package");

  int8_t result = protocol_obtain(server->pack, server->size_pack, server->protocol);
  if (result != SUCC) return result;

  return database_driver(server);
}