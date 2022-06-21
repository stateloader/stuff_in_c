#ifndef DEVICE_H_
#define DEVICE_H_

#include "configs.h"

typedef struct Device {
  int8_t status;
  int8_t exec;
  int32_t size_user;
  char user[SBUFF];
} dvce_t;

int8_t device_driver(dvce_t *device);

#endif