#ifndef DATABASE_H_
#define DATABASE_H_

#include <stdint.h>
#include "sstring.h"
#include "sconfig.h"

#define decode_rwbit(rwb) (rwb & (1 << RWBIT))

typedef struct DataBase {
  uint8_t status;
  uint8_t reqbyte;
  int8_t model;
  int8_t trigg;
  int8_t rwbit;
  uint32_t size_recv;
  uint32_t size_resp;
  char recv[SBUFF];
  char resp[FBUFF];
} data_t;

int8_t database_driver(data_t *database);

inline static int8_t decode_model(uint8_t reqbyte) {
  System_Message("Inside decode_model\n");
  for (int8_t model = 0; model < LNIBB; model++) {
    if (reqbyte & (1 << model)) return model;
  }
  System_Message("--seems there's no model assigned.");
  return NBIT;
}

inline static int8_t decode_trigg(uint8_t reqbyte) {
  System_Message("Inside decode_trigg\n");
  for (int8_t trigg = LNIBB; trigg < (HNIBB - 1); trigg++) {
    if (reqbyte & (1 << trigg)) return trigg;
  }
  return 0;
}

inline static int8_t database_reader_check(int32_t size_resp, int32_t size_file) {
  if(check_cnum(size_resp, size_resp)) {
    System_Message("--size_resp and size_file don't match.");
    return FAIL;
  }
  return SUCC;
}
#endif