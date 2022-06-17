#ifndef DEVICE_H_
#define DEVICE_H_

#include <stdint.h>
#include "cconfig.h"
#include "client.h"

int8_t device_driver(client_t *client, int8_t choice);

inline static int8_t device_binder_check(client_t *client) {

  if (!check_term(client->rqst, client->size_rqst)) {
    System_Message("Failed to terminate request");
    return FLEE;

  } else if (!check_rdfm(client->rqst, client->size_rqst)) {
    System_Message("Failed to put delimiter on request");
    return FLEE;
  }
  return DONE;
}

#endif
