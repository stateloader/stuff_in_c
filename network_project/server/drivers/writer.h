#ifndef WRITER_H_
#define WRITER_H_

#include <stdint.h>
#include "sconfig.h"
#include "saker/models.h"

typedef struct WriteItem {
  const uint8_t model;
  const char *path;
} write_item;

typedef struct Writer {
  uint8_t status;
  write_item *item;
  int32_t size_appd;
  char appd[SBUFF];
  char resp[SBUFF];
  FILE *file;
} write_t;

int8_t write_driver(write_t *writer);


inline static int8_t fileopen_check(FILE *file) {
  if (!file) {
    System_Message("failed to open file");
    return FAIL;
  }
  return SUCC;
}

inline static int8_t fileappd_check(int32_t size_writ, int32_t size_appd, FILE *file) {
  if (!check_cnum(size_writ, size_appd)) {
    System_Message("differend sizes written/appendsize");
    if (file) fclose(file);
    return FAIL;
  }
  if (file) fclose(file);
  return SUCC;
} 

#endif