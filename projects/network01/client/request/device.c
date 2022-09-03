/*--------------------------------------------------------------------------------------------DEVICE

--------------------------------------------------------------------------------------------------*/

#include <string.h>
#include <stdlib.h>
#include "../jackIO/cstrings.h"
#include "../jackIO/scanner.h"
#include "../jackIO/screener.h"
#include "device.h"

static void datetime_attach(reqt_t *request) {
/*Attaches a timestamp to request-packages.*/

  strncat(request->datetime, __DATE__, TBUFF);
  strncat(request->datetime, " ", TBUFF);
  strncat(request->datetime, __TIME__, TBUFF);
  request->size_datm = string_size(SBUFF, request->datetime);
  return;
}

static void protocol_attach(reqt_t *request) {

  request->package[request->size_pack - 4] = request->protocol[TINDX];
  request->package[request->size_pack - 3] = request->protocol[PINDX];
  request->package[request->size_pack - 2] = request->protocol[CINDX];
  request->package[request->size_pack - 1] = '\0';
  
  return;
}

static void ledcolor_attach(uint8_t perf_byte, devc_t *device) {

  if (perf_byte & (1 << PERF0))
    device->size_note = string_copy(SBUFF, device->dvce_note, "Red");
  if (perf_byte & (1 << PERF1))
    device->size_note = string_copy(SBUFF, device->dvce_note, "Blue");
  if (perf_byte & (1 << PERF2))
    device->size_note = string_copy(SBUFF, device->dvce_note, "Green");
  return;
}

static void push_device(reqt_t *request) {

  devc_t device = {.size_note = 0};

  datetime_attach(request);
  ledcolor_attach(request->protocol[PINDX], &device);

  request->size_pack = (request->size_user + request->size_datm + device.size_note + POFFS);

  request->username[request->size_user - 1] = DELIM;
  request->datetime[request->size_datm - 1] = DELIM;
  device.dvce_note[device.size_note - 1] = DELIM;

  strncat(request->package, request->username, request->size_pack);
  strncat(request->package, request->datetime, request->size_pack);
  strncat(request->package, device.dvce_note, request->size_pack);

  protocol_attach(request);
  return;
}

static void pull_device(reqt_t *request) {
/*Creates a Device pull-request. Only PROTOCOL (and terminator) necessary.*/

  request->size_pack = POFFS;
  protocol_attach(request);
}

void device_driver(reqt_t *request) {
  
  if ((request->protocol[CINDX] & (1 << PPREQ)))
    push_device(request);
  else
    pull_device(request);
  return;
}
