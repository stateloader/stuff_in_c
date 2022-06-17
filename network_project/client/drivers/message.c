/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                   MESSAGE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "cstring.h"
#include "scanner.h"
#include "message.h"

static void fetch_datetime(client_t *client) {
  strncat(client->mesg.datm, __DATE__, 16);
  strncat(client->mesg.datm, " ", 16);
  strncat(client->mesg.datm, __TIME__, 16);
  client->mesg.size_datm = TBUFF;
}

static int8_t message_reader(client_t *client) {

  Render_Header("SEND", "Enter topic and message.");

  fetch_datetime(client);

  client->mesg.size_topc = scan_driver(client->mesg.topc, CBUFF, "topic");
  client->mesg.size_mesg = scan_driver(client->mesg.mesg, CBUFF, "message");

  client->user[client->size_user - 1] = '|';
  client->mesg.datm[client->mesg.size_datm - 1] = '|';
  client->mesg.topc[client->mesg.size_topc - 1] = '|';
  client->mesg.mesg[client->mesg.size_mesg - 1] = '|';

  client->size_rqst = (
    client->size_user + client->mesg.size_datm +
    client->mesg.size_topc + client->mesg.size_mesg + 2
  );
  return message_reader_check(client);
}

static int8_t message_binder(client_t *client) {

  strncat(client->rqst, client->user, client->size_rqst);
  strncat(client->rqst, client->mesg.datm, client->size_rqst);
  strncat(client->rqst, client->mesg.topc, client->size_rqst);
  strncat(client->rqst, client->mesg.mesg, client->size_rqst);

  client->rqst[client->size_rqst - 2] = RWMSG;
  client->rqst[client->size_rqst - 1] = '\0';
  client->user[client->size_user - 1] = '\0';

  buffer_flush(client->mesg.datm, client->mesg.size_datm);
  buffer_flush(client->mesg.topc, client->mesg.size_topc);
  buffer_flush(client->mesg.mesg, client->mesg.size_mesg);

  return message_binder_check(client);
}

int8_t message_driver(client_t *client) {

  if (message_reader(client) < 0)
    return FLEE;
  else
    return message_binder(client);
}