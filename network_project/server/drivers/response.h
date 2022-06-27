#ifndef RESPONSE_H_
#define RESPONSE_H_

#include "configs.h"
#include "server.h"

int8_t response_driver(server_t *server);

inline static int8_t response_driver_check(int32_t size_send, int32_t size_pack) {
  if (size_send != size_pack) {
    System_Message("size differences send/pack");
    return FAIL;
  }
  return SUCC;
}

#endif