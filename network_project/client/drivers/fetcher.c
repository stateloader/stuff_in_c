/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                   FETCHER
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include "cstring.h"
#include "scanner.h"
#include "fetcher.h"

int8_t fetch_driver(client_t *client, int8_t choice) {
  if (choice == TEMP)
    client->rqst[0] = RDTP;
  else
    client->rqst[0] = RDMG;
  client->size_rqst = 2;
  return DONE;
}