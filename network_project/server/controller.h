#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "connect/connection.h"

typedef struct Controller {
  uint16_t status, error;
  uint8_t protocol[3];
  size_t size_recv;
  size_t size_resp;
  char receive[SBUFF];
  char response[RBUFF];
} cont_t;

void control_driver(cont_t *control, serv_t *server);

#endif
