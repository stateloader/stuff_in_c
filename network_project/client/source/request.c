/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                   REQUEST
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include "cstring.h"
#include "message.h"
#include "device.h"
#include "request.h"

static rqst_item table_items[] = {
  {TMESG, message_driver}, {TDVCE, device_driver}
};

int8_t request_driver(rqst_t *request) {

  for (size_t i = 0; i < ARRAY_SIZE(table_items); i++) {
    if (request->protocol[TBYTE] & (1 << table_items[i].task))
      return table_items[i].func(request);
  }
  System_Message("couldn't read request-call");
  return FAIL;
}