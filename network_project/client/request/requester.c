/*----------------------------------------------------------------------------------------------------------------REQUESTER
                                                                                    
-------------------------------------------------------------------------------------------------------------------------*/
#include <string.h>
#include "../connect/connection.h"
#include "../system/cstrings.h"
#include "device.h"
#include "message.h"
#include "requester.h"

static void validate_push(reqt_t *request, uint8_t *state, uint16_t *error) {
/*Some checks before a push-request being sent to the server.*/

  size_t delim_count = 0;
  for (size_t i = 0; i < request->size_pack; i++)
    delim_count += (request->package[i] == DELIM) ? 1 : 0;

  if (delim_count != request->pack_delm) {
    *state |= (1 << ERROR); *error |= (1 << PDERR);
  }//wrong delimiter-format.
  if (request->size_pack < POFFS) {
    *state |= (1 << ERROR); *error |= (1 << PSERR);
  }//corrupted size on package.
  if (request->package[request->size_pack - 1] != '\0') {
    *state |= (1 << ERROR); *error |= (1 << PTERR);
  }//package isn't nullterminated.

  return;
}

static void validate_pull(reqt_t *request, uint8_t *state, uint16_t *error) {
/*Some checks before a pull-request being sent to the server.*/

  if (request->package[request->size_pack - 1] != '\0') {
    *state |= (1 << ERROR); *error |= (1 << PTERR);
  }//package isn't nullterminated.

  return;
}
static reqt_item table_items[] = {
  {TMESG, message_driver}, {TDVCE, device_driver}
};

void datetime_attach(reqt_t *request) {
/*Attaches a timestamp to request-packages.*/

  strncat(request->datetime, __DATE__, TBUFF);
  strncat(request->datetime, " ", TBUFF);
  strncat(request->datetime, __TIME__, TBUFF);
  request->size_datm = string_size(request->datetime, SBUFF);

  return;
}

void protocol_attach(reqt_t *request) {
/*Attaches the PROTOCOL (and nullterminator) to request-packages.*/

  request->package[request->size_pack - 4] = request->protocol[TBIDX];
  request->package[request->size_pack - 3] = request->protocol[ABIDX];
  request->package[request->size_pack - 2] = request->protocol[EBIDX];
  request->package[request->size_pack - 1] = '\0';

  return;
}

void request_driver(reqt_t *request, uint8_t *state, uint16_t *error) {
/*Iterates through the flags in the TBIDX-byte of the PROTOCOL and loads the associated driver.*/

  request->protocol[EBIDX] |= (1 << VALID);

  for (size_t i = 0; i < ARRAY_SIZE(table_items); i++) {
    if (request->protocol[TBIDX] & (1 << table_items[i].table))
      table_items[i].func(request, state, error);
  }
  if (*state & (1 << ERROR))
    request->package[request->size_pack - 2] &= ~(1 << VALID);

  size_t size_send = send(request->sock_desc, request->package, request->size_pack, 0);
  System_Message("sending request to server.");
  return;
}