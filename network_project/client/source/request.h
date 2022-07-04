#ifndef REQUEST_H_
#define REQUEST_H_

#define INIT_MESG 0
#define INIT_DVCE 1

#include "controller.h"

typedef struct Request {
  int32_t socket;
  uint8_t *protocol;
  int32_t size_send;
  int32_t size_user;
  int32_t size_pack;
  char *user;
  char pack[SBUFF];
} rqst_t;

int8_t delimiter_check(rqst_t *request, int32_t expected);
int8_t datetime_append(char *datetime);
int8_t protocol_append(rqst_t *request);
int8_t request_driver(rqst_t *request);


inline static int8_t protocol_append_checks(rqst_t *request) {
  
  if (request->pack[request->size_pack - 4] & (0 << UNBIT)) {
    System_Message("TBYTE not unsigned");
    return FAIL;
  }
  if (request->pack[request->size_pack - 3] & (0 << UNBIT)) {
    System_Message("ABYTE not unsigned");
    return FAIL;
  }
  if (request->pack[request->size_pack - 2] & (0 << UNBIT)) {
    System_Message("SBYTE not unsigned");
    return FAIL;
  }
  if (request->pack[request->size_pack - 1] != '\0') {
    System_Message("package not nullterminated.");
    return FAIL;
  }
  return SUCC;
}

#endif