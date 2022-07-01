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

static int8_t validate_account(server_t *server) {

  int8_t result = 0;

  result = database_reader(server);
  if (result != SUCC) return result;
  
  pars_t parser = {0};

  parser.protocol = server->protocol;
  parser.size_pack = string_copy(parser.pack, server->pack, SBUFF);
  parser.size_data = string_copy(parser.data, server->resp, SBUFF);

  result = account_driver(&parser);
  if (result != SUCC) return result;

  if (server->protocol[SBYTE] & (1 << SETUP))
    return database_writer(server);

  return SUCC;
}

static int8_t database_driver(server_t *server) {
  Message_Info("connecting database");

  if (server->protocol[ABYTE] & (1 << RWBIT)) {
    Message_Info("writing to database");
    return database_writer(server);
  } else {
    Message_Info("reading from database");
    return database_reader(server);
  }
}

static int8_t protocol_fetcher(server_t *server) { 

  server->protocol[TBYTE] = server->pack[server->size_pack - 4];
  server->protocol[ABYTE] = server->pack[server->size_pack - 3];
  server->protocol[SBYTE] = server->pack[server->size_pack - 2];

  PrintByte(server->protocol[TBYTE]);
  PrintByte(server->protocol[ABYTE]);
  PrintByte(server->protocol[SBYTE]);

  return protocol_fetcher_check(server);
}

int8_t receive_driver(server_t *server) {
  Message_Info("inside receive driver");

  server->size_pack = recv(server->conn.sock_clnt, server->pack, SBUFF, 0);

  int8_t result = protocol_fetcher(server);
  if (result == FAIL) return result;

  if (server->protocol[SBYTE] & (1 << VALID))
    return database_driver(server);
  else
    return validate_account(server);
}