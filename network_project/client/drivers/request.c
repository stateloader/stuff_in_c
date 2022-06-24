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

void request_driver(rqst_t *request) {
  System_Message("Inside request_driver");

  for (size_t i = 0; i < ARRAY_SIZE(rqst_items); i++) {
    if (request->protocol[TINDX] & (1 << rqst_items[i].task))
      rqst_items[i].func(request);
  }
  return;
}