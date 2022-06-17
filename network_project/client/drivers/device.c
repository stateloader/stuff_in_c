/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    DEVICE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "cstring.h"
#include "scanner.h"
#include "device.h"

static int8_t device_binder(client_t *client, int8_t choice) {

  client->size_rqst = string_copy(client->rqst, client->user, CBUFF);
  client->rqst[client->size_rqst - 1] = '|';
  client->size_rqst += 2;

  if (choice == DRED)
    client->rqst[client->size_rqst - 2] = RARED;
  else if (choice == DBLU)
    client->rqst[client->size_rqst - 2] = RABLU;
  else
    client->rqst[client->size_rqst - 2] = RAGRN;
  client->rqst[client->size_rqst - 1] = '\0';

  return device_binder_check(client);
}
int8_t device_driver(client_t *client, int8_t choice) {
  return device_binder(client, choice);
}