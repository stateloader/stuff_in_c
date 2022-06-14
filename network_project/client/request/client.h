#ifndef CLIENT_H_
#define CLIENT_H_

#include <stdint.h>
#include "command/utils/cconfig.h"

typedef struct Client  {
  int16_t status;
  int32_t request_size;
  int32_t username_size;
  int32_t password_size;
  int32_t response_size;
  char username[CBUFF];
  char password[CBUFF];
  char command[CBUFF];
  char request[CBUFF];
  uint8_t response[RBUFF];
} client_t;

#endif