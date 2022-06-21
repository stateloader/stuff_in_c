/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                   REQUEST
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include "cstring.h"
#include "message.h"
#include "device.h"
#include "request.h"

int8_t request_driver(rqst_t *request) {
  System_Message("Inside request_driver");

  dvce_t device = {.status = 1};
  mesg_t message = {.status = 1};

  switch(fetch_task(request->protocol[2])) {

  case INIT_MESG:
    message.size_user = string_copy(message.user, request->user, SBUFF);
    message.exec = request->protocol[1];
    message_driver(&message);
    break;

  case INIT_DVCE:
    device.size_user = string_copy(device.user, request->user, SBUFF);
    device.exec = request->protocol[1];
    device_driver(&device);
    break;

  default:
    System_Message("No task detected");
    return FAIL;

    
  }  
  return SUCC;

}