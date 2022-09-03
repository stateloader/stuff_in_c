#ifndef DEVICE__H_
#define DEVICE__H_

#include "../configs.h"
#include "request.h"

typedef struct Device {
  size_t size_note;
  char dvce_note[SBUFF];
} devc_t;

void device_driver(reqt_t *request);

#endif
