/*------------------------------------------------------------------------------------------------------------------------
                                                                                                             DEVICE MODULE
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
    client->request[0] = RADR;
  else if (choice == DBLU)
    client->request[0] = RADB;
  else
    client->request[0] = RADG;
  client->request_size = 2;
  return QUIT;
}