#ifndef DATABASE_H_
#define DATABASE_H_

#include <stdint.h>
#include "sstring.h"
#include "configs.h"

#define decode_rwbit(rwb) (rwb & (1 << RWBIT))

typedef struct DataBase {
  uint8_t status;
  int8_t protocol[3];
  uint32_t size_recv;
  uint32_t size_resp;
  char recv[SBUFF];
  char resp[FBUFF];
} data_t;

int8_t database_driver(data_t *database);

#endif