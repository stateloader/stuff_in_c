/*------------------------------------------------------------------------------------------------------------------------
                                                                                                            MESSAGE MODULE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "utils/cstring.h"
#include "utils/scanner.h"
#include "message.h"

static char topc[CBUFF] = {'\0'};
static char mesg[CBUFF] = {'\0'};

static int8_t message_reader(client_t *client) {

  Render_Header("SEND", "Enter (namn för nu), topic and message.");

  client->size_user = scan_driver(client->user, CBUFF, "testname");
  client->user[client->size_user - 1] = '|';

  int32_t size_topc = scan_driver(topc, CBUFF, "topic");
  topc[size_topc - 1] = '|';
  
  int32_t size_mesg = scan_driver(mesg, CBUFF, "message");
  mesg[size_mesg - 1] = '|';

  client->size_rqst = (size_topc + size_mesg + client->size_user + 2);

  return DONE;
}
static int8_t message_binder(client_t *client) {

  strncat(client->rqst, client->user, client->size_rqst);
  strncat(client->rqst, topc, client->size_rqst);
  strncat(client->rqst, mesg, client->size_rqst);

  client->rqst[client->size_rqst - 2] = RWMG;
  client->user[client->size_user - 1] = '\0';

  buffer_flush(topc, CBUFF);
  buffer_flush(topc, CBUFF);

  return DONE;
}

int8_t message_driver(client_t *client) {
  
  message_reader(client);
  return message_binder(client);
  return DONE;
}