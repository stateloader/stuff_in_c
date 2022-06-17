#ifndef WRITER_H_
#define WRITER_H_

#include <stdint.h>
#include "sconfig.h"
#include "saker/models.h"

typedef struct Writer {
  int8_t model, action;
  int32_t size_appd;
  int32_t size_path;
  char appd[SBUFF];
  char path[PBUFF];
  FILE *file;
} write_t;

int8_t write_driver(write_t *writer);

inline static int8_t fileop_checker(write_t *writer) {
  if (!writer->file) {
    System_Message("failed to open file");
    return FLEE;
  }
  return SUCC;
}

inline static int8_t append_checker(int32_t size_fwrite, write_t *writer) {

  if (!check_cnum(size_fwrite, writer->size_appd)) {
    System_Message("written size and my size off");
    return FAIL;
  }
  return SUCC;
}
#endif