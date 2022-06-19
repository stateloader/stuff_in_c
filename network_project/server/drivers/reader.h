/*------------------------------------------------------------------------------------------------------------------------
                                                                                                               READ HEADER
--------------------------------------------------------------------------------------------------------------------------
description to be
------------------------------------------------------------------------------------------------------------------------*/
#ifndef READER_H_
#define READER_H_

#include <stdint.h>
#include "sconfig.h"
#include "saker/models.h"

typedef struct ReadItem {
  const uint8_t model;
  const char *path;
} read_item;

typedef struct Reader {
  uint8_t status;
  read_item *item;
  int32_t size_file;
  char file_data[FBUFF];
  FILE *file;
} read_t;

int8_t read_driver(read_t *reader);

inline static int8_t fileread_check(int32_t size_file, FILE *file) {
  System_Message("Inside fileread_check");

  if (size_file == 0) {
    System_Message("--file is empty");
    if (file) fclose(file);
    return FAIL;
  }
  if (file) fclose(file);
  return SUCC;
} 
#endif