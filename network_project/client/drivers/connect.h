#ifndef CONNECT_H_
#define CONNECT_H_

#include <stdint.h>
#include "cconfig.h"
#include "client.h"

int8_t connect_driver(client_t *client, int8_t choice);

inline static int8_t connect_reader_check(client_t *client) {

  if (!check_delm(client->user, client->size_user)) {
    System_Message("Failed to put delimiter on username");
    return FLEE;
  } else if (!check_delm(client->pass, client->size_pass)) {
    System_Message("Failed to put delimiter on password");
    return FLEE;
  } else if (client->size_rqst < 2) {
    System_Message("Failed to fetch request-size");
    return FLEE;
  }
  return SUCC;
}

inline static int8_t connect_binder_check(client_t *client) {

  if (!check_term(client->user, client->size_user)) {
    System_Message("Failed to teterminate username");
    return FLEE;
  } else if (!check_term(client->pass, client->size_pass)) {
    System_Message("Failed to teterminate password");
    return FLEE;
  } else if (!check_term(client->rqst, client->size_rqst)) {
    System_Message("Failed to teterminate password");
    return FLEE;
  }
  return DONE;
}
#endif
