#ifndef WRITER_H_
#define WRITER_H_

#include <stdint.h>
#include "sconfig.h"
#include "saker/models.h"

typedef struct WriterRouteItem{
  const uint8_t model;
  const uint8_t action;
  const char *wpackage;
  const char *filepath; 
} wrim_t;

typedef struct Writer {
  uint8_t init;
  wrim_t witem;
} write_t;

int8_t write_driver(write_t *writer);

#endif