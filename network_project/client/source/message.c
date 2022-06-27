/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                   MESSAGE
--------------------------------------------------------------------------------------------------------------------------
Logic dealing with creation of message-requests; send to or read historical records from the server.
------------------------------------------------------------------------------------------------------------------------*/

#include "scanner.h"
#include "message.h"

static int8_t protocol_append(rqst_t *request) {
//desc
  request->pack[request->size_pack - 4] = request->protocol[TINDX];
  request->pack[request->size_pack - 3] = request->protocol[EINDX];
  request->pack[request->size_pack - 2] = request->protocol[FINDX];
  request->pack[request->size_pack - 1] = '\0';

  return protocol_append_check(request->pack, request->size_pack);
}

static int8_t datetime_append(char *datetime) {
//desc
  strncat(datetime, __DATE__, TBUFF);
  strncat(datetime, " ", TBUFF);
  strncat(datetime, __TIME__, TBUFF);
  datetime[TBUFF - 1] = DELIM;

  return datetime_append_check(datetime, TBUFF);
}

static int8_t message_binder(rqst_t *request, mesg_t *message) {
//desc
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

  System_Message(request->pack);

  return protocol_append(request);
}

static int8_t message_writer(rqst_t *request, mesg_t *message) {
//desc
  int8_t result = 0;

  result = datetime_append(message->datm);
  if (!result) return result;

  message->size_topc = scan_driver(message->topc, SBUFF, "topic");
  message->size_mesg = scan_driver(message->mesg, SBUFF, "message");

  return message_binder(request, message);
}

static int8_t message_reader(rqst_t *request) {
//desc
  request->size_pack = POFFS;
  return protocol_append(request);
}

int8_t message_driver(rqst_t *request) {
//desc
  mesg_t message = {0};
  if (request->protocol[EINDX] & (1 << RWBIT))
    return message_writer(request, &message);
  else
    return message_reader(request);
}