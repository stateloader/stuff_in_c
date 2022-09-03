#ifndef CDRIVER_H_
#define CDRIVER_H_

#include "configs.h"
#include "connect/connect.h"

typedef struct ClientDriver {
  uint8_t state;
  uint8_t protocol[3];
  cent_t client;
} driver_t;

void client_driver(driver_t *driver);

#endif
