#ifndef RECEIVER_H_
#define RECEIVER_H_

#include "../configs.h"
#include "models.h"

typedef struct Receiver {
  uint8_t *protocol;
  size_t size_pack;
  char package[RBUFF];
  size_t tabl_delm;
  size_t amnt_delm;
  size_t amnt_rows;
  mmod_t *table_mesg;
  dmod_t *table_dvce;
} recv_t;

void receive_driver(recv_t *receive, uint8_t *state, uint16_t *error);

#endif
