/*------------------------------------------------------------------------------------------------------------------------
                                                                                                               READ HEADER
--------------------------------------------------------------------------------------------------------------------------
description to be
------------------------------------------------------------------------------------------------------------------------*/
#ifndef READER_H_
#define READER_H_

#include "configs.h"
#include "server.h"

typedef int8_t (*read_func)(server_t *server);

typedef struct ReadItem {
  const uint8_t flag;
  read_func func;
} read_item;

int8_t database_reader(server_t *server);

inline static int8_t reader_file_open_check(FILE *file) {
  if (file == NULL) {
    Message_Info("failed to open file");
    return FAIL;
  }
  return SUCC;
}

inline static int8_t reader_file_data_check(int32_t size_recv) {
  if (size_recv < 4) {
    Message_Info("to little something reader file");
    return FAIL;
  }
  return SUCC;
}

#endif