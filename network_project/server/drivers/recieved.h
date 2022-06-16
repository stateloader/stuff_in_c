#ifndef RECIEVED_H_
#define RECIEVED_H_

#include <stdint.h>
#include "sconfig.h"
#include "server.h"

int8_t recieved_driver(server_t *server);

inline static int8_t recieved_check(server_t *server, uint8_t *endbytes) {

  if (!check_term(server->recv, server->size_recv)) {
    System_Message("Recvied request isn't terminated");
    return FAIL;
  } else if (!check_tedl(server->recv, server->size_recv)) {
    System_Message("Third last byte isn't delimiter.");
    return FAIL;
  }

  fetch_endb(server->endbyte, server->recv, server->size_recv);

  uint8_t match = 0;
  for (int8_t i = 0; i < 8; i++)
    match += (server->endbyte == endbytes[i]) ? 1 : 0;

  if (match != 1) {
    System_Message("Corrupted endbyte.\n");
    return FAIL;
  }

  uint8_t mask = server->endbyte;
  if (!parse_rewr(mask)) {
    System_Message("Init read from database.\n");
    server->dborder = INITR;
  } else {
    System_Message("Init write to database.\n");
    server->dborder = INITW;
  }
  return SUCC;
}

#endif