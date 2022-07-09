#ifndef DEVICE_H_
#define DEVICE_H_

#include "../system/configs.h"
#include "requester.h"

#define DVCER 0
#define DVCEW 1

typedef struct Device {
  size_t size_push;
  char dvcepush[SBUFF];
} devc_t;

void device_driver(reqt_t *request, uint8_t *state, uint16_t *error);

#endif
