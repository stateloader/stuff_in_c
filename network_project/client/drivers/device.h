#ifndef DEVICE_H_
#define DEVICE_H_

#include "configs.h"

typedef struct Device {
  uint8_t status;
} dvce_t;

int8_t dvce_driver(void *device);

#endif