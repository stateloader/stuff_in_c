/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                   FETCHER
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include "cstring.h"
#include "scanner.h"
#include "fetcher.h"

static int8_t fetch_binder(client_t *client, int8_t choice) {

  client->size_rqst = string_copy(client->rqst, client->user, CBUFF);
  client->rqst[client->size_rqst - 1] = '|';
  client->size_rqst += 2;

  if (choice == TEMP)
    client->rqst[client->size_rqst - 2] = RDTMP;
  else
    client->rqst[client->size_rqst - 2] = RDMSG;
  client->rqst[client->size_rqst - 1] = '\0';

  return fetch_binder_check(client);
}

int8_t fetch_driver(client_t *client, int8_t choice) {
  return fetch_binder(client, choice);
}