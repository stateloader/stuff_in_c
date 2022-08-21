#ifndef RECEIVER_H_
#define RECEIVER_H_

#include "../system/configs.h"
#include "models.h"

#define RECV_MESG 0x81
#define RECV_DVCE 0x82

typedef struct Receiver {
  int32_t sock_desc;
  uint8_t protocol[3];
  size_t amnt_rows;
  size_t size_pack;
  char package[RBUFF];
  mmod_t *table_mesg;
  dmod_t *table_dvce;
} recv_t;

void receive_driver(recv_t *receive, uint8_t *state, uint16_t *error);

#endif
