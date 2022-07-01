#ifndef DEVICE_H_
#define DEVICE_H_

#include "controller.h"
#include "request.h"

typedef struct PushItem {
  const uint8_t bit;
  char *str;
} push_item;

typedef struct Device {
  int32_t size_push;
  char datm[TBUFF];
  char push[SBUFF];
} dvce_t;

int8_t device_driver(rqst_t *request);

#endif