#ifndef RECEIVE_H_
#define RECEIVE_H_

#include "configs.h"
#include "models.h"

typedef struct Receive {
  int8_t status;
  uint8_t protocol[3];
  char recv[FBUFF];
  int32_t size_recv;
  size_t entry_delim;
  int32_t count_delm;
  int32_t count_rows;
  mmod_t *table_mesg;
  dmod_t *table_dvce;
} recv_t;

typedef void (*recv_func)(recv_t *receive);

typedef struct RecieveItem {
  const uint8_t table;
  const int32_t delim;
  recv_func func;
} recv_item;

int8_t receive_driver(recv_t *receive);

#endif