/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                   MESSAGE
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/

#include "scanner.h"
#include "message.h"

static void fetch_datetime(char *datetime) {
  strncat(datetime, __DATE__, 16);
  strncat(datetime, " ", 16);
  strncat(datetime, __TIME__, 16);
}

static int8_t message_create(mesg_t *message) {
  System_Message("Inside message_create");

  fetch_datetime(message->datm);
  message->size_topc = scan_driver(message->topc, SBUFF, "topic");
  message->size_mesg = scan_driver(message->mesg, SBUFF, "message");
  return SUCC;
}

int8_t message_driver(mesg_t *message) {
  System_Message("Inside message_driver");
  return message_create(message);
}