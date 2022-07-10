#ifndef CDRIVER_H_
#define CDRIVER_H_

#include "system/configs.h"
#include "connect/connection.h"

typedef struct ClientDriver {
  uint8_t state;
  uint16_t error;
  uint8_t protocol[3];
  clnt_t client;
} dver_t;

void client_driver(dver_t *driver);

#endif