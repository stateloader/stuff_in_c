#ifndef DEVICE_H_
#define DEVICE_H_

#include "configs.h"
#include "request.h"

typedef struct DeviceItem {
  const uint8_t execb;
  const char *dbstr;
} dvce_item;

typedef struct Device {
  int8_t status;
  uint8_t protocol[3];
  int32_t size_user;
  char user[SBUFF];
} dvce_t;

void device_driver(rqst_t *request);

#endif