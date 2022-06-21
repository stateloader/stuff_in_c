/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                   REQUEST
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include "cstring.h"
#include "message.h"
#include "device.h"
#include "request.h"

void protocol_adder(rqst_t *request) {

  request->rqst[request->size_rqst - (POFFS - 0)] = request->protocol[0];
  request->rqst[request->size_rqst - (POFFS - 1)] = request->protocol[1];
  request->rqst[request->size_rqst - (POFFS - 2)] = request->protocol[2];
  request->rqst[request->size_rqst - (POFFS - 3)] = '\0';

  if (!check_term(request->rqst, request->size_rqst)) {
    System_Message("not nullterminated");
    request->status = 0;
  }
}

void request_driver(rqst_t *request) {
  System_Message("Inside request_driver");

  switch(fetch_task(request->protocol[2])) {
  case INIT_MESG:
    message_driver(request);
    break;
  case INIT_DVCE:
    device_driver(request);
    break;
  default:
    System_Message("No task detected");
  }
  return;
}