/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                   MESSAGE
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/

#include "scanner.h"
#include "message.h"

static void fetch_datetime(char *datetime) {
  strncat(datetime, __DATE__, TBUFF);
  strncat(datetime, " ", TBUFF);
  strncat(datetime, __TIME__, TBUFF);
  return;
}

static void message_binder(rqst_t *request, mesg_t *message) {
  System_Message("Inside message create");

  if (!message->status) return;

  request->size_rqst = (
    request->size_user + message->size_topc + message->size_mesg + TBUFF + POFFS
  );
  
  request->user[request->size_user - 1] = DELIM;
  message->datm[TBUFF - 1] = DELIM;
  message->topc[message->size_topc - 1] = DELIM;
  message->mesg[message->size_mesg - 1] = DELIM;

  strncat(request->rqst, request->user, request->size_rqst);
  strncat(request->rqst, message->datm, request->size_rqst);
  strncat(request->rqst, message->topc, request->size_rqst);
  strncat(request->rqst, message->mesg, request->size_rqst);

  protocol_adder(request);
  return;
}

static void message_create(rqst_t *request, mesg_t *message) {
  System_Message("Inside message create");

  fetch_datetime(message->datm);
  message->size_topc = scan_driver(message->topc, SBUFF, "topic");
  message->size_mesg = scan_driver(message->mesg, SBUFF, "message");

  message_create_checks(message);
  message_binder(request, message);
  return;
}

static void message_readDB(rqst_t *request) {
  System_Message("Inside message readDB");

  request->size_rqst = POFFS;
  protocol_adder(request);
  return;
}

void message_driver(rqst_t *request) {
  System_Message("Inside message_driver");

  mesg_t message = {.status = 1};
  switch(message_exec_check(request->protocol[1])) {

  case MESG_CRTE:
    message_create(request, &message);
    break;

  case MESG_READ:
    message_readDB(request);
    break;

  default:
    System_Message("shouldn't be here at all, message_driver");
    message.status = 0;
    request->status = 0;
  }

  return;
}