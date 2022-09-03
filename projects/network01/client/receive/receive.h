#ifndef RECEIVE__H_
#define RECEIVE__H_

#include "../configs.h"
#include "models.h"

typedef struct Receiver {
  int32_t sock_desc;
  uint8_t protocol[3];
  size_t size_rows;
  size_t size_pack;
  char package[RBUFF];
  mmod_t *table_mesg;
  dmod_t *table_dvce;
} recv_t;

void receive_driver(recv_t *receive);

#endif
