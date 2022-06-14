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

  Print_Header("SEND", "Enter (namn för nu), topic and message.");

  client->username_size = scan_driver(client->username, CBUFF, "testname");
  client->username[client->username_size - 1] = '|';

  int32_t size_topc = scan_driver(topc, CBUFF, "topic");
  topc[size_topc - 1] = '|';
  
  int32_t size_mesg = scan_driver(mesg, CBUFF, "message");
  mesg[size_mesg - 1] = '|';

  client->request_size = (size_topc + size_mesg + client->username_size + 2);

  return SUCC;
}

static int8_t message_request(client_t *client) {

  strncat(client->request, client->username, client->request_size);
  strncat(client->request, topc, client->request_size);
  strncat(client->request, mesg, client->request_size);

  client->request[client->request_size - 2] = RWMG;


  client->username[client->username_size - 1] = '\0';
  buffer_flush(topc, CBUFF);
  buffer_flush(topc, CBUFF);

  uint8_t reqmask = client->request[client->request_size - 2];
  PrintByte(reqmask);

  return QUIT;
}

int8_t message_driver(client_t *client) {
  
  message_reader(client);
  return message_request(client);
  return QUIT;
}