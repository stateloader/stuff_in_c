#ifndef WRITER_H_
#define WRITER_H_

#include <stdint.h>
#include "sconfig.h"

typedef struct Writer {
  uint8_t status;
} write_t;

int8_t write_driver(write_t *writer);

#endif