/*------------------------------------------------------------------------------------------------------------------DEVICE

------------------------------------------------------------------------------------------------------------------------*/

/*TODO  
  -se över device-struct.
  -skriva nått kort i headern.
*/

#include <string.h>
#include "../system/cstrings.h"
#include "../system/scanner.h"
#include "device.h"

static void dvce_scan(uint8_t push, devc_t *device) {
/*A short string being attached to the push-package mapped by the user's choice of LED-colour.*/

  if (push & (1 << ATTR0))
    device->size_push = string_copy(device->dvcepush, "RED", SBUFF);
  if (push & (1 << ATTR1))
    device->size_push = string_copy(device->dvcepush, "BLU", SBUFF);
  if (push & (1 << ATTR2))
    device->size_push = string_copy(device->dvcepush, "GRN", SBUFF);
    
  return;
}

static void dvce_push(devc_t *device, reqt_t *request) {
/*Creates a Device push-request by binding all relevant data into a canonical string.*/

  datetime_attach(request);
  dvce_scan(request->protocol[ABIDX], device);

  request->size_pack = (request->size_user + request->size_datm + device->size_push + POFFS);

  request->username[request->size_user - 1] = DELIM;
  request->datetime[request->size_datm - 1] = DELIM;
  device->dvcepush[device->size_push - 1] = DELIM;

  strncat(request->package, request->username, request->size_pack);
  strncat(request->package, request->datetime, request->size_pack);
  strncat(request->package, device->dvcepush, request->size_pack);

  protocol_attach(request);
  
  return;
}

static void dvce_pull(reqt_t *request) {
/*Creates a Device pull-request. Only PROTOCOL (and terminator) necessary.*/

  request->size_pack = POFFS;
  protocol_attach(request);
}

void device_driver(reqt_t *request, uint8_t *state, uint16_t *error) {
/*The driver assigns member 'pack_delm' - basically how many delimiters an row/entry/instance of Device has while
 *being stored in the database - before a route being determined based on RWBIT in PROTOCOL.*/

  request->pack_delm = DDVCE;
  devc_t device = {.size_push = 0};
  int32_t route = (request->protocol[EBIDX] & (1 << RWBIT)) ? 1 : 0;

  switch (route) {
  case 0:
    dvce_pull(request);
    break;
  case 1:
    dvce_push(&device, request);
    break;
  default:
    *state |= (1 << ERROR); *error |= (1 << SDERR);
  }
  return;
}
