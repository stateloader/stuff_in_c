/*----------------------------------------------------------------------------------RESPONSE DRIVER
The response

When a response being created from the server it always read or write to a database depending on whether the request was
of type pull(read something from database) or push(write/append to database). This source-file, through its driver, sewing
all logic in the RESPONSE-module togheter.  
-------------------------------------------------------------------------------------------------*/


#include <sys/socket.h>
#include "../jackIO/cstrings.h"
#include "reader.h"
#include "writer.h"
#include "response.h"

static void protocol_attach(resp_t *response) {
/*Attaches the PROTOCOL (and nullterminator) to response-packages.*/

  response->response[response->size_resp - 4] = response->protocol[TINDX];
  response->response[response->size_resp - 3] = response->protocol[PINDX];
  response->response[response->size_resp - 2] = response->protocol[CINDX];
  response->response[response->size_resp - 1] = '\0';

  return;
}

static void database_pull(resp_t *response) {
 /*Struct-variable 'reader' points at protocol and heads down the 'read_driver' before fetched content being copied to
  *the response-package.*/ 

  read_t reader = {.size_cont = 0};
  reader.protocol = response->protocol;

  read_driver(&reader);
  response->size_resp = string_copy(RBUFF, response->response, reader.content) - 1;
  return;
}

static void database_push(resp_t *response) {
 /*Struct-variable 'writer' points at data stored among the response-members before append-logic taking place inside
  *the 'write_driver'.*/

  write_t writer = {.size_appd = response->size_recv};
  writer.protocol = response->protocol;
  writer.append = response->received;

  write_driver(&writer);

  return;
}

static void validate_resp(resp_t *response) {

  response->size_resp += POFFS;
  protocol_attach(response);
  return;
}

void response_driver(resp_t *response) {
/*State of the RWBIT in Received PROTOCOL decides which database-route to take - push or pull - before the crated
 *response being validated and sent.*/

  System_Message("creating response.");
  int32_t database_route = (response->protocol[CINDX] & (1 << PPREQ)) ? 1 : 0;

  switch (database_route) {
  case 0:
    database_pull(response);
  break;
  case 1:
    database_push(response);
  break;
  default:
    System_Message("creating response.");
  return;
  }
  validate_resp(response);
  
  size_t size_send = send(response->client_sock, response->response, response->size_resp, 0);
  System_Message("sending response to client.");
  close(response->client_sock);
  return;
}
