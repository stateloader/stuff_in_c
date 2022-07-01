#ifndef CONNECT_H
#define CONNECT_H

#include "configs.h"
#include "session.h"

#define CONN_ 0
#define LOGN_ 1
#define SIGN_ 2
#define VALD_ 3
#define DONE_ 4
#define EXIT_ 5

int8_t connect_driver(client_t *client, char *address, int32_t port);

static inline uint8_t scanner_size_check(int32_t size_user, int32_t size_pass) {
  if (size_user < 1 || size_pass < 1 ) {
    Message_Info("something went south while scanning username and/or password");
    return FAIL;
  }
  return SUCC;
}  

#endif