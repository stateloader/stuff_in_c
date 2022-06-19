#include "message.h"

static int8_t message_create() {
  System_Message("Inside message_create");
  return SUCC;
}

int8_t message_driver(mesg_t *message) {
  System_Message("Inside message_driver");

  System_Message(message->user);
  return SUCC;
}