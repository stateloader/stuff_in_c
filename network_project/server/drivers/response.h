#ifndef RESPONSE_H_
#define RESPONSE_H_

#include "configs.h"
#include "server.h"

typedef int8_t (*resp_func)(server_t *server);

typedef struct ResponseItem{
  const uint8_t byte;
  resp_func func;
} resp_item;

int8_t response_driver(server_t *server, int8_t control);

inline static int8_t response_driver_check(int32_t size_send, int32_t size_pack) {
  if (size_send != size_pack) {
    Message_Info("size differences send/pack");
    return FAIL;
  }
  return SUCC;
}

#endif