/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    DEVICE
--------------------------------------------------------------------------------------------------------------------------
Logic dealing with creation of device requests; send (interact with device) or read historical records from the server.
------------------------------------------------------------------------------------------------------------------------*/

#include "cstring.h"
#include "device.h"

static int8_t device_package(rqst_t *request, dvce_t *device) {
  
  datetime_append(device->datm);
  request->size_pack = (request->size_user + device->size_push + TBUFF + POFFS);

  request->user[request->size_user - 1] = DELIM;
  device->push[device->size_push - 1] = DELIM;

  strncat(request->pack, request->user, request->size_pack);
  strncat(request->pack, device->datm, request->size_pack);
  strncat(request->pack, device->push, request->size_pack);

  int8_t result = 0;

  result = protocol_append(request->pack, request->size_pack, request->protocol);
  if (result != SUCC) return result;

  result = delimiter_check(request->pack, request->size_pack, DDVCE); // check
  if (result != SUCC) return result;  

  return SUCC;
}

static push_item push_items[] = {
  {ATTR0, "RED"}, {ATTR1, "BLU"}, {ATTR2, "GRN"}
};

static int8_t device_writer(rqst_t *request, dvce_t *device) {
  
  for (size_t i = 0; i < ARRAY_SIZE(push_items); i++) {
    if (request->protocol[ABYTE] & (1 << push_items[i].flag))
      device->size_push = string_copy(device->push, push_items[i].code, SBUFF);
  }
  return device_package(request, device);
}

static int8_t device_reader(rqst_t *request) {

  request->size_pack = POFFS;
  return protocol_append(request->pack, request->size_pack, request->protocol);
}

int8_t device_driver(rqst_t *request) {

  dvce_t device = {0};

  if (request->protocol[ABYTE] & (1 << RWBIT))
    return device_writer(request, &device);
  else
    return device_reader(request);
}