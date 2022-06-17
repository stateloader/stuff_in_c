#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <stdint.h>
#include "cconfig.h"
#include "client.h"

int8_t message_driver(client_t *client);

inline static int8_t message_reader_check(client_t *client) {

  if (!check_delm(client->user, client->size_user)) {
    System_Message("Failed to put delimiter on username");
    return FLEE;
  } else if (!check_delm(client->mesg.datm, client->mesg.size_datm)) {
    System_Message("Failed to put delimiter on datetime");
    return FLEE;
  } else if (!check_delm(client->mesg.topc, client->mesg.size_topc)) {
    System_Message("Failed to put delimiter on topic");
    return FLEE;
  } else if (!check_delm(client->mesg.mesg, client->mesg.size_mesg)) {
    System_Message("Failed to put delimiter on topic");
    return FLEE;
  }
  return SUCC;
}

inline static int8_t message_binder_check(client_t *client) {

  if (!check_term(client->user, client->size_user)) {
    System_Message("Failed to reterminate username");
    return FLEE;
  } else if (!check_term(client->rqst, client->size_rqst)) {
    System_Message("Failed to terminate request");
    return FLEE;
  }
  return DONE;
}

#endif

