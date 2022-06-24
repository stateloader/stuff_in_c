/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                   MESSAGE
--------------------------------------------------------------------------------------------------------------------------
logic dealing with user messages; send- and read-requests to the server.
------------------------------------------------------------------------------------------------------------------------*/

#include "scanner.h"
#include "message.h"

static void protocol_adder(rqst_t *request) {

  request->rqst[request->size_rqst - 4] = request->protocol[TINDX];
  request->rqst[request->size_rqst - 3] = request->protocol[EINDX];
  request->rqst[request->size_rqst - 2] = request->protocol[FINDX];
  request->rqst[request->size_rqst - 1] = '\0';
}


static void fetch_datetime(char *datetime) {
//desc
  strncat(datetime, __DATE__, TBUFF);
  strncat(datetime, " ", TBUFF);
  strncat(datetime, __TIME__, TBUFF);
  return;
}

static void message_binder(rqst_t *request, mesg_t *message) {
//desc
  if (!message->status) return;

  request->size_rqst = (
    request->size_user + 2 + message->size_topc + message->size_mesg + TBUFF + POFFS
  );
  request->user[request->size_user - 1] = DELIM;
  message->datm[TBUFF - 1] = DELIM;
  message->topc[message->size_topc - 1] = DELIM;
  message->mesg[message->size_mesg - 1] = DELIM;

  strncat(request->rqst, "1|", request->size_rqst);
  strncat(request->rqst, request->user, request->size_rqst);
  strncat(request->rqst, message->datm, request->size_rqst);
  strncat(request->rqst, message->topc, request->size_rqst);
  strncat(request->rqst, message->mesg, request->size_rqst);

  protocol_adder(request);
  return;
}

static void message_write(rqst_t *request, mesg_t *message) {

  fetch_datetime(message->datm);
  message->size_topc = scan_driver(message->topc, SBUFF, "topic");
  message->size_mesg = scan_driver(message->mesg, SBUFF, "message");
  message_binder(request, message);

  return;
}

static void message_read(rqst_t *request) {
//desc
  request->size_rqst = POFFS;
  protocol_adder(request);
  return;
}

void message_driver(rqst_t *request) {
//desc
  mesg_t message = {.status = 1};
  if(request->protocol[EINDX] & (1 << RWBIT))
    message_write(request, &message);
  else
    message_read(request);
  return;
}