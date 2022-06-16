/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    DEVICE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "utils/cstring.h"
#include "utils/scanner.h"
#include "device.h"

int8_t device_driver(client_t *client, int8_t choice) {
  if (choice == DRED)
    client->rqst[0] = RADR;
  else if (choice == DBLU)
    client->rqst[0] = RADB;
  else
    client->rqst[0] = RADG;
  client->size_rqst = 2;
  return DONE;
}