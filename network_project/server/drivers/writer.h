#ifndef WRITER_H_
#define WRITER_H_

#include <stdint.h>
#include "sconfig.h"
#include "saker/models.h"

typedef struct WriteItem{
  const uint8_t model, action;
  const uint32_t size_package;
  const char *package;
  const char *filepath;
} wrim_t;

typedef struct Writer {
  uint8_t status;
  wrim_t witem;
  FILE *file;
} write_t;

int8_t write_driver(write_t *writer);

inline static int8_t write_fileop_checker(write_t *writer) {
  if (!writer->file) {
    System_Message("failed to open file");
    return FAIL;
  } else if (!check_term(writer->witem.package, writer->witem.size_package)) {
    System_Message("package is not nullterminated");
    return FAIL;
  }
  return SUCC;
}

inline static int8_t write_append_checker(int32_t size_package, int32_t size_append) {
  if (size_package != size_append) {
    System_Message("size on appended package differs from recieved.");
    return FAIL;
  }
  return SUCC;
}

#endif