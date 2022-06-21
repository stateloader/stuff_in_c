#ifndef REQUEST_H_
#define REQUEST_H_

#define INIT_MESG 0
#define INIT_DVCE 1

#include "configs.h"

typedef struct Request {
  uint8_t status;
  int8_t protocol[3];
  int32_t size_user;
  int32_t size_rqst;
  char user[SBUFF];
  char rqst[SBUFF];
} rqst_t;

int8_t request_driver(rqst_t *request);

inline static int8_t fetch_task(int8_t task) {
  if (task & (1 << TMESG))
    return INIT_MESG;
  else
    return INIT_DVCE;
}
#endif