#ifndef RECEIVE_H_
#define RECEIVE_H_

#include "controller.h"
#include "models.h"

typedef struct Receiver {
  int32_t socket;
  uint8_t *protocol;
  int32_t tabl_delm;
  int32_t amnt_delm;
  int32_t amnt_rows;
  int32_t size_recv;
  int32_t size_user;
  char *user;
  char recv[FBUFF];
  mmod_t *table_mesg;
  dmod_t *table_dvce;
} recv_t;

int8_t receive_driver(recv_t *receive);

inline static int8_t protocol_obtain_checks(recv_t *receive) {
  
  if (receive->recv[receive->size_recv - 1] != '\0') {
    System_Message("package not nullterminated.");
    return FAIL;
  }
  if (receive->protocol[TBYTE] & (0 << UNBIT)) {
    System_Message("TBYTE most significant not set");
    return FAIL;
  }
  if (receive->protocol[ABYTE] & (0 << UNBIT)) {
    System_Message("ABYTE most significant not set");
    return FAIL;
  }
  if (receive->protocol[SBYTE] & (0 << UNBIT)) {
    System_Message("SBYTE most significant not set");
    return FAIL;
  }
  if (receive->recv[receive->size_recv - 1] != '\0') {
    System_Message("package not nullterminated.");
    return FAIL;
  }
  if (receive->protocol[SBYTE] == 0xFF) {
    System_Message("Server's having a bad day.");
    return FAIL;
  }
  return SUCC;
}

inline static void release_memory(recv_t *receive) {

  if (receive->table_mesg) {
    free(receive->table_mesg);
    receive->table_mesg = NULL;
  }
  if (receive->table_dvce) {
    free(receive->table_dvce);
    receive->table_dvce = NULL;
  }
}
#endif