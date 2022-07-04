/*-----------------------------------------------------------------------------------------------------------------REQUEST

------------------------------------------------------------------------------------------------------------------------*/
#include "cstring.h"
#include "message.h"
#include "device.h"
#include "request.h"

int8_t datetime_append(char *datetime) {
/*creates and appends datetime to the (a) request-package*/

  strncat(datetime, __DATE__, TBUFF);
  strncat(datetime, " ", TBUFF);
  strncat(datetime, __TIME__, TBUFF);
  datetime[TBUFF - 1] = DELIM;

  return SUCC;
}

int8_t delimiter_check(rqst_t *request, size_t expected) {
/*makes sure the package has the right amount of delimiters, is canonical*/

  size_t amnt_delim = 0;

  for (size_t i = 0; i < request->size_pack; i++)
    amnt_delim += (request->pack[i] == DELIM) ? 1 : 0;
    
  if (amnt_delim != expected) {
    System_Message("corrupted format on package.");
    return FAIL;
  }
  return SUCC;
}

int8_t protocol_append(rqst_t *request) {
/*Assigns the protocol to the package*/

  request->pack[request->size_pack - 4] = request->protocol[TBYTE];
  request->pack[request->size_pack - 3] = request->protocol[ABYTE];
  request->pack[request->size_pack - 2] = request->protocol[SBYTE];
  request->pack[request->size_pack - 1] = '\0';

  return protocol_append_checks(request);
}

typedef int8_t (*rqst_func)(rqst_t *request);

typedef struct RequestItem {
  const uint8_t task;
  rqst_func func;
} rqst_item;


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