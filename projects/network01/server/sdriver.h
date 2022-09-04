#ifndef SDRIVER__H_
#define SDRIVER__H_

#include "connect/connect.h"

typedef struct ServerDriver {
  uint8_t status;
  serv_t server;
} driver_t;

void server_driver(driver_t *driver);

#endif
