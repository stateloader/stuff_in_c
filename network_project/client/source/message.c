/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                   MESSAGE
--------------------------------------------------------------------------------------------------------------------------
Logic dealing with creation of message-requests; send to or read historical records from the server.
------------------------------------------------------------------------------------------------------------------------*/

#include "scanner.h"
#include "message.h"

static int8_t message_binder(rqst_t *request, mesg_t *message) {

  request->size_pack = (
    request->size_user + message->size_topc + message->size_mesg + TBUFF + POFFS
  );

  request->user[request->size_user - 1] = DELIM;
  message->topc[message->size_topc - 1] = DELIM;
  message->mesg[message->size_mesg - 1] = DELIM;

  strncat(request->pack, request->user, request->size_pack);
  strncat(request->pack, message->datm, request->size_pack);
  strncat(request->pack, message->topc, request->size_pack);
  strncat(request->pack, message->mesg, request->size_pack);

  return protocol_append(request->pack, request->size_pack, request->protocol);
}

static int8_t message_writer(rqst_t *request, mesg_t *message) {

  if(!datetime_append(message->datm))
    return FAIL;
    
  message->size_topc = scan_driver(message->topc, SBUFF, "topic");
  message->size_mesg = scan_driver(message->mesg, SBUFF, "message");
  return message_binder(request, message);
}

static int8_t message_reader(rqst_t *request) {

  request->size_pack = POFFS;
  return protocol_append(request->pack, request->size_pack, request->protocol);
}

int8_t message_driver(rqst_t *request) {

  mesg_t message = {0};

  if (request->protocol[ABYTE] & (1 << RWBIT))
    return message_writer(request, &message);
  else
    return message_reader(request);
}