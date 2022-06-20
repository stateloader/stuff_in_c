#include "scanner.h"
#include "message.h"

static void fetch_datetime(mesg_t *message) {
  strncat(message->datm, __DATE__, 16);
  strncat(message->datm, " ", 16);
  strncat(message->datm, __TIME__, 16);
}

static int8_t message_create(mesg_t *message) {
  System_Message("Inside message_create");

  fetch_datetime(message);
  message->size_topc = scan_driver(message->topc, SBUFF, "topic");
  message->size_mesg = scan_driver(message->mesg, SBUFF, "message");
  return SUCC;//message_driver_check(message);
}

int8_t message_driver(mesg_t *message) {
  System_Message("Inside message_driver");
  return message_create(message);
}