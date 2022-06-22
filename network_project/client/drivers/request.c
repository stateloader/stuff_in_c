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

  request->rqst[request->size_rqst - 4] = request->protocol[TINDX];
  request->rqst[request->size_rqst - 3] = request->protocol[EINDX];
  request->rqst[request->size_rqst - 2] = request->protocol[FINDX];
  request->rqst[request->size_rqst - 1] = '\0';

  if (!check_term(request->rqst, request->size_rqst)) {
    System_Message("not nullterminated");
    request->status = 0;
  }
}

void request_driver(rqst_t *request) {
  System_Message("Inside request_driver");

  switch(fetch_task(request->protocol[TINDX])) {
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