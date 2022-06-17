#ifndef DATABASE_H_
#define DATABASE_H_

#include <stdint.h>
#include "sconfig.h"
#include "server.h"

int8_t database_driver(server_t *server);

inline static int8_t check_model(uint8_t endbyte) {
  System_Message("Inside check_model\n");

  for (int8_t i = 0; i < LNIBB; i++) {
    if (endbyte & (1 << i))
      return i;
  }
  return FLEE;
}

inline static int8_t check_action(uint8_t endbyte) {
  System_Message("Inside check_model\n");

  for (int8_t i = LNIBB; i < (HNIBB - 1); i++) {
    if (endbyte & (1 << i))
      return i;
  }
  return FLEE;
}

#endif