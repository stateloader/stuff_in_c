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

static char datm[CBUFF] = {'\0'};
static char topc[CBUFF] = {'\0'};
static char mesg[CBUFF] = {'\0'};

static int32_t fetch_datetime(void) {
  strncat(datm, __DATE__, 16);
  strncat(datm, " ", 16);
  strncat(datm, __TIME__, 16);
  int32_t size_datm = string_size(datm, CBUFF);
  datm[size_datm - 1] = '|';
  return size_datm;
}

static int8_t message_reader(client_t *client) {

  Render_Header("SEND", "Enter (namn för nu), topic and message.");

  uint32_t size_datm = 0, size_topc = 0, size_mesg = 0; 
  
  size_datm = fetch_datetime();

  size_topc = scan_driver(topc, CBUFF, "topic");
  topc[size_topc - 1] = '|';
  
  size_mesg = scan_driver(mesg, CBUFF, "message");
  mesg[size_mesg - 1] = '|';

  client->size_user = scan_driver(client->user, CBUFF, "testname");
  client->user[client->size_user - 1] = '|';

  client->size_rqst = (size_datm + size_topc + size_mesg + client->size_user + 2);

  return DONE;
}

static int8_t message_binder(client_t *client) {

  strncat(client->rqst, datm, client->size_rqst);
  strncat(client->rqst, topc, client->size_rqst);
  strncat(client->rqst, mesg, client->size_rqst);
  strncat(client->rqst, client->user, client->size_rqst);

  

  client->rqst[client->size_rqst - 2] = RWMG;
  client->user[client->size_user - 1] = '\0';

  buffer_flush(datm, CBUFF);
  buffer_flush(topc, CBUFF);
  buffer_flush(mesg, CBUFF);

  return DONE;
}

int8_t message_driver(client_t *client) {
  
  message_reader(client);
  return message_binder(client);
}