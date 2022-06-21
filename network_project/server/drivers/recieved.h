#ifndef RECIEVED_H_
#define RECIEVED_H_

#include "configs.h"
#include "database.h"
#include "server.h"

int8_t recieved_driver(server_t *server);

inline static int8_t recieved_driver_check(data_t *database) {

  if (!check_term(database->recv, database->size_recv)) {
    System_Message("request isn't terminated");
    return FAIL;

  } else if (!check_tedl(database->recv, database->size_recv)) {
    System_Message("last delimiter missing.");
    return FAIL;
  }
  return SUCC;
}
#endif