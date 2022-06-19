#include "message.h"

int8_t mesg_driver(void *message) {
  System_Message("Inside message_driver");
  return SUCC;
}