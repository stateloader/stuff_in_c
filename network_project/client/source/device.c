/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    DEVICE
--------------------------------------------------------------------------------------------------------------------------
Logic dealing with creation of device requests; send (interact with device) or read historical records from the server.
------------------------------------------------------------------------------------------------------------------------*/
#include "cstring.h"
#include "device.h"

static push_item push_items[] = {
  {EXEC0, "RED"}, {EXEC1, "BLU"}, {EXEC2, "GRN"}
};

static int8_t device_binder(rqst_t *request, dvce_t *device) {
  
  request->user[request->size_user - 1] = DELIM;
  device->push[device->size_push - 1] = DELIM;

  strncat(request->pack, request->user, request->size_pack);
  strncat(request->pack, device->datm, request->size_pack);
  strncat(request->pack, device->push, request->size_pack);

  return protocol_append(request->pack, request->size_pack, request->protocol);
}

static int8_t device_writer(rqst_t *request, dvce_t *device) {

  datetime_append(device->datm);

  for (size_t i = 0; i < ARRAY_SIZE(push_items); i++) {
    if (request->protocol[EINDX] & (1 << push_items[i].bit))
      device->size_push = string_copy(device->push, push_items[i].str, SBUFF);
  }
  request->size_pack = (request->size_user + device->size_push + TBUFF + POFFS);

  return device_binder(request, device);
}

static int8_t device_reader(rqst_t *request) {

  request->size_pack = POFFS;
  return protocol_append(request->pack, request->size_pack, request->protocol);
}

int8_t device_driver(rqst_t *request) {

  dvce_t device = {0};

  if (request->protocol[EINDX] & (1 << RWBIT))
    return device_writer(request, &device);
  else
    return device_reader(request);
}