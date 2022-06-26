/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                   REQUEST
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include "cstring.h"
#include "message.h"
#include "device.h"
#include "request.h"


static rqst_item rqst_items[] = {
  {TMESG, message_driver},
  {TDVCE, device_driver}
};

int8_t request_driver(rqst_t *request) {

  for (size_t i = 0; i < ARRAY_SIZE(rqst_items); i++) {
    if (request->protocol[TINDX] & (1 << rqst_items[i].task))
      return rqst_items[i].func(request);
  }
  System_Message("couldn't read request-call");
  return FAIL;
}