#ifndef SDRIVER_H_
#define SDRIVER_H_

#include "connect/connection.h"

typedef struct ServerDriver {
  uint16_t status, error;
  serv_t server;
} dver_t;

void server_driver(dver_t *driver);

#endif
