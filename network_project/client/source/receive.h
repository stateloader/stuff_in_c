#ifndef RECEIVE_H_
#define RECEIVE_H_

#include "configs.h"
#include "models.h"

typedef struct TableMeta {
  size_t entry_delim;
  int32_t count_delm;
  int32_t count_rows;
} meta_t;

typedef struct Receiver {
  uint8_t *protocol;
  int32_t size_recv;
  char recv[FBUFF];
  void *table;
  mmod_t *table_mesg;
  dmod_t *table_dvce;
  meta_t meta;
} recv_t;

typedef int8_t (*recv_func)(recv_t *receive);

typedef struct RecieveItem {
  const uint8_t table;
  const int32_t delim;
  recv_func func;
} recv_item;

int8_t receive_driver(recv_t *receive);

#endif