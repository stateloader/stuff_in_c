/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    READER
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include "socket.h"
#include "sstring.h"
#include "receive.h"
#include "writer.h"
#include "reader.h"
#include "account.h"

static int8_t protocol_obtain(server_t *server) { 

  server->protocol[TBYTE] = server->pack[server->size_pack - 4];
  server->protocol[ABYTE] = server->pack[server->size_pack - 3];
  server->protocol[SBYTE] = server->pack[server->size_pack - 2];

  return protocol_obtain_check(server);
}

static int8_t database_driver(server_t *server) {
  
  if (server->protocol[ABYTE] & (1 << RWBIT)) {
    System_Message("writing to database");
    return database_writer(server);
  } else {
    System_Message("reading from database");
    return database_reader(server);
  }
}

int8_t receive_driver(server_t *server) {

  server->size_pack = recv(server->conn.sock_clnt, server->pack, SBUFF, 0);

  int8_t result = protocol_obtain(server);
  if (result == FAIL) return result;
  
  return database_driver(server);
}