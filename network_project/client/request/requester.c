/*----------------------------------------------------------------------------------------------------------------REQUESTER
info info info                                                                                           
-------------------------------------------------------------------------------------------------------------------------*/
#include <string.h>
#include "../command/cstrings.h"
#include "device.h"
#include "message.h"
#include "requester.h"

void datetime_attach(reqt_t *request) {
/*Creating a timestamp attached to every push/write request-packages.*/

  strncat(request->datetime, __DATE__, TBUFF);
  strncat(request->datetime, " ", TBUFF);
  strncat(request->datetime, __TIME__, TBUFF);
  request->size_datm = string_size(request->datetime, SBUFF);

  return;
}

void protocol_attach(reqt_t *request) {
/*Attaches the PROTOCOL (set during the client's endeavours in COMMAND MODULE). These 4 bytes, regardless push/write or
 *pull/read requests, ends every request sent to the server.*/

  request->package[request->size_pack - 4] = request->protocol[TBIDX];
  request->package[request->size_pack - 3] = request->protocol[ABIDX];
  request->package[request->size_pack - 2] = request->protocol[EBIDX];
  request->package[request->size_pack - 1] = '\0';

  return;
}

void push_check(reqt_t *request, uint8_t *state, uint16_t *error) {
/*A few checks before the package being thrown at the server.*/

  size_t delim_count = 0;

  for (size_t i = 0; i < request->size_pack; i++)
    delim_count += (request->package[i] == DELIM) ? 1 : 0;

  if (delim_count != request->pack_delm) {
    *state |= (1 << ERROR); *error |= (1 << PDERR);
  }
  if (request->size_ctrl != request->size_pack) {
    *state |= (1 << ERROR); *error |= (1 << PSERR);
  }
  if (request->package[request->size_pack - 1] != '\0') {
    *state |= (1 << ERROR); *error |= (1 << PTERR);
  }
  return;
}

void pull_check(reqt_t *request, uint8_t *state, uint16_t *error) {
/*check package is null-terminated*/
  if (request->package[request->size_pack - 1] != '\0') {
    *state |= (1 << ERROR); *error |= (1 << PTERR);
  }
  return;
}

static reqt_item table_items[] = {
  {TMESG, message_driver},
  {TDVCE, device_driver}
};

void request_driver(reqt_t *request, uint8_t *state, uint16_t *error) {
/*Iterates through the flags in the TBIDX-byte of the PROTOCOL and loads the associated driver*/

  size_t match = 0;
  for (size_t i = 0; i < ARRAY_SIZE(table_items); i++) {
    if (request->protocol[TBIDX] & (1 << table_items[i].table)) {
      table_items[i].func(request, state, error); match++;
    }
  } if (!match) {
    *state |= (1 << ERROR); *error |= (1 << IIERR);
  }
  return;
}
