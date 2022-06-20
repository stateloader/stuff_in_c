/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                   REQUEST
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include "cstring.h"
#include "message.h"
#include "request.h"
/*
static const uint8_t TMESG = 0x00;
static const uint8_t TDVCE = 0x01;

static int8_t request_canonical_mesg(rqst_t *request, mesg_t *message) {
  System_Message("inside canonical mesg");
  return SUCC;
}

static int8_t request_mesg(rqst_t *request) {
  System_Message("inside fomat_mesg");

  mesg_t message = {.status = 1};

  if ((message.size_user = string_copy(message.user, request->user, SBUFF)) < 1)
    return KILL;
  else if (message_driver(&message) < 1)
    return KILL;
  else 
    return request_canonical_mesg(request, &message);
}

static int8_t request_dvce(rqst_t *request) {
  System_Message("inside fomay_mesg");
  return SUCC;
}
*/
int8_t request_driver(rqst_t *request) {
  System_Message("Inside request_driver");
  return SUCC;
/*
  if (request->rqst_byte & (1 << TMESG))
    return request_mesg(request);

  else if (request->rqst_byte & (1 << TDVCE))
    return request_dvce(request);

  else
    return FAIL;
    */
}