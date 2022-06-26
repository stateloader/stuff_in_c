/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    DEVICE
--------------------------------------------------------------------------------------------------------------------------
Logic dealing with creation of device requests; send (interact with device) or read historical records from the server.
------------------------------------------------------------------------------------------------------------------------*/
#include "cstring.h"
#include "device.h"

static int8_t fetch_datetime(char *datetime) {
  strncat(datetime, __DATE__, TBUFF);
  strncat(datetime, " ", TBUFF);
  strncat(datetime, __TIME__, TBUFF);
  datetime[TBUFF - 1] = DELIM;

  return SUCC;
}

static int8_t protocol_append(rqst_t *request) {

  request->pack[request->size_pack - 4] = request->protocol[TINDX];
  request->pack[request->size_pack - 3] = request->protocol[EINDX];
  request->pack[request->size_pack - 2] = request->protocol[FINDX];
  request->pack[request->size_pack - 1] = '\0';

  return SUCC;
}

static int8_t device_writer(rqst_t *request) {
  System_Message("Inside device writer");

  char datm[TBUFF] = {'\0'};
  fetch_datetime(datm);

  request->size_pack = (request->size_user + TBUFF + POFFS);

  request->user[request->size_user - 1] = DELIM;

  strncat(request->pack, request->user, request->size_pack);
  strncat(request->pack, datm, request->size_pack);

  return protocol_append(request);
}

static int8_t device_reader(rqst_t *request) {
  System_Message("Inside device reader");

  request->size_pack = POFFS;
  return protocol_append(request);
}

int8_t device_driver(rqst_t *request) {
  System_Message("Inside device driver");

  if (request->protocol[EINDX] & (1 << RWBIT))
    return device_writer(request);
  else
    return device_reader(request);
}
