#ifndef DATABASE_H_
#define DATABASE_H_

#include <stdint.h>
#include "sstring.h"
#include "sconfig.h"
#include "server.h"

int8_t database_driver(server_t *server);

inline static int8_t decode_model_check(uint8_t endbyte) {

  System_Message("Inside check_model\n");
  for (int8_t i = 0; i < LNIBB; i++) {
    if (endbyte & (1 << i))
      return i;
  }
  System_Message("seems there's no model assigned");
  return FLEE;
}

inline static int8_t decode_action_check(uint8_t endbyte) {

  System_Message("Inside check_model\n");
  for (int8_t i = LNIBB; i < (HNIBB - 1); i++) {
    if (endbyte & (1 << i))
      return i;
  }
  System_Message("seems there's no action assigned");
  return FAIL;
}

inline static int8_t database_writer_check(server_t *server) {

  if (!check_cnum(server->writer.size_appd, server->size_recv)) {
    System_Message("stringsizes doesent match.\n");
    return FAIL;
  } else if (!string_comp(server->writer.appd, server->recv, server->size_recv)) {
    System_Message("recv-string and string to be appended doesn't compare");
    return FAIL;
  } else if (!check_endf(server->writer.appd, server->writer.size_appd)) {
    System_Message("not delimiterneded");
    return FAIL;
  }
  return SUCC;
}
#endif