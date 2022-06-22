#ifndef DEVICE_H_
#define DEVICE_H_

#include "configs.h"
#include "request.h"

typedef struct Device {
  int8_t status;
  uint8_t protocol[3];
  int32_t size_user;
  char user[SBUFF];
} dvce_t;

int8_t device_driver(rqst_t *request);

#endif