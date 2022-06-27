#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "configs.h"
#include "request.h"

typedef struct Message {
  int32_t size_user;
  int32_t size_topc;
  int32_t size_mesg;
  char datm[TBUFF];
  char user[SBUFF];
  char topc[SBUFF];
  char mesg[SBUFF];
} mesg_t;

int8_t message_driver(rqst_t *request);

//----------------------------------------------------------------------------------------------------ERROR CHECKS MESSAGE
/*
inline static int8_t protocol_append_check(const char *package, const uint32_t size_package) {
  if (!check_term(package, size_package)) {
    System_Message("--Error-- package not nullterminated.");
    return FAIL;
  }
  return SUCC;
}

inline static int8_t datetime_append_check(const char *package, const uint32_t size_package) {
  if (!check_delm(package, size_package)) {
    System_Message("--Error-- no delimiter added to datetime.");
    return FAIL;
  }
  return SUCC;
}
*/
#endif