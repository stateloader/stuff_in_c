/*------------------------------------------------------------------------------------------------------------------DEVICE
info info info
------------------------------------------------------------------------------------------------------------------------*/

#include <string.h>
#include "../system/cstrings.h"
#include "../system/scanner.h"
#include "device.h"

static void dvce_scan(uint8_t push, devc_t *device) {
/*A short string being attached to the dvce push-package corresponding with whatever LED-colour the user choosed.*/

  if (push & (1 << ATTR0))
    device->size_push = string_copy(device->dvcepush, "RED", SBUFF);
  if (push & (1 << ATTR1))
    device->size_push = string_copy(device->dvcepush, "BLU", SBUFF);
  if (push & (1 << ATTR2))
    device->size_push = string_copy(device->dvcepush, "GRN", SBUFF);

  return;
}

static void dvce_push(devc_t *device, reqt_t *request) {
/*Creates/binds a string - a canonical package of type 'device entry' - to be received and stored in server database.*/

  System_Message("Initializes device push request.");

  datetime_attach(request);
  dvce_scan(request->protocol[ABIDX], device);

  request->size_pack = (
    request->size_user + request->size_datm + device->size_push + POFFS  // func för va args kanske
  );

  request->username[request->size_user - 1] = DELIM;
  request->datetime[request->size_datm - 1] = DELIM;
  device->dvcepush[device->size_push - 1] = DELIM;

  strncat(request->package, request->username, request->size_pack);
  strncat(request->package, request->datetime, request->size_pack);
  strncat(request->package, device->dvcepush, request->size_pack);

  protocol_attach(request);
  request->size_ctrl = string_size(request->package, SBUFF);
  
  return;
}

static void dvce_pull(reqt_t *request) {
/*Attaches just the PROTOCOL to the package if the client has requested to read device-records*/
  System_Message("Initializes device pull request.");

  request->size_pack = POFFS;
  protocol_attach(request);
}


void device_driver(reqt_t *request, uint8_t *state, uint16_t *error) {

  request->pack_delm = DDVCE;
  devc_t device = {.size_push = 0};
  int32_t route = (request->protocol[EBIDX] & (1 << RWBIT)) ? DVCEW : DVCER;

  switch (route) {

  case DVCER:
    dvce_pull(request);
    pull_check(request, state, error);
    break;

  case DVCEW:
    dvce_push(&device, request);
    push_check(request, state, error);
    break;

  default:
    *state |= (1 << ERROR); *error |= (1 << SDERR);
    break;
  }
  return;
}
