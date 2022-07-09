#ifndef SDRIVER_H_
#define SDRIVER_H_

#include "connect/connection.h"

typedef struct ServerDriver {
  uint16_t status, error;
  int32_t client_sock_desc;
  uint8_t protocol[3];
  void *table;
} dver_t;

void server_driver(dver_t *driver, serv_t *server);

#endif
