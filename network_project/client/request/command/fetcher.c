/*------------------------------------------------------------------------------------------------------------------------
                                                                                                               DATA MODULE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include "utils/cstring.h"
#include "utils/scanner.h"
#include "fetcher.h"

int8_t fetch_driver(client_t *client, int8_t choice) {
  if (choice == TEMP)
    client->request[0] = RDTP;
  else
    client->request[0] = RDMG;
  client->request_size = 2;
  return QUIT;
}