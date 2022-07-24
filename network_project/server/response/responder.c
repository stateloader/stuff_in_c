/*-----------------------------------------------------------------------------------------------------------------RESPONSE
When a response being created from the server it always read or write to a database depending on whether the request was
of type pull(read something from database) or push(write/append to database). This source-file, through its driver, sewing
all logic in the RESPONSE-module togheter.                                  
-------------------------------------------------------------------------------------------------------------------------*/

#include <sys/socket.h>
#include "../system/cstrings.h"
#include "reader.h"
#include "writer.h"
#include "responder.h"

static void protocol_attach(resp_t *response) {
/*Attaches the PROTOCOL (and nullterminator) to response-packages.*/

  response->response[response->size_resp - 4] = response->protocol[TBIDX];
  response->response[response->size_resp - 3] = response->protocol[ABIDX];
  response->response[response->size_resp - 2] = response->protocol[EBIDX];
  response->response[response->size_resp - 1] = '\0';

  return;
}

static void database_pull(resp_t *response, uint16_t *state, uint16_t *error) {
 /*Struct-variable 'reader' points at protocol and heads down the 'read_driver' before fetched content being copied to
  *the response-package.*/ 

  read_t reader = {.size_cont = 0};
  reader.protocol = response->protocol;

  read_driver(&reader, state, error);
  response->size_resp = string_copy(response->response, reader.content, RBUFF) - 1;

  return;
}

static void database_push(resp_t *response, uint16_t *state, uint16_t *error) {
 /*Struct-variable 'writer' points at data stored among the response-members before append-logic taking place inside
  *the 'write_driver'.*/

  write_t writer = {.size_appd = response->size_recv};
  writer.protocol = response->protocol;
  writer.append = response->received;

  write_driver(&writer, state, error);

  return;
}

static void validate_resp(resp_t *response, uint16_t *state) {
/*Making room for PROTOCOL (and terminator). If any error has accured the VALID-flag will be cleared, else set. A
 *cleared flag will be interpreted by the client as something went wrong on server-side.*/
  
  response->size_resp += POFFS;
  if (*state & (1 << ERROR))
    response->protocol[EBIDX] &= ~(1 << VALID);
  else
    response->protocol[EBIDX] |= (1 << VALID);
  protocol_attach(response);

  return;
}

void response_driver(resp_t *response, uint16_t *state, uint16_t *error) {
/*State of the RWBIT in Received PROTOCOL decides which database-route to take - push or pull - before the crated
 *response being validated and sent.*/

  System_Message("Creating response.");
  int32_t database_route = (response->protocol[EBIDX] & (1 << RWBIT)) ? 1 : 0;

  switch (database_route) {
  case 0:
    database_pull(response, state, error);
  break;
  case 1:
    database_push(response, state, error);
  break;
  default:
    *state |= (1 << ERROR); *error |= (1 << SDERR);
  return;
  }
  validate_resp(response, state);
  
  size_t size_send = send(response->client_sock_desc, response->response, response->size_resp, 0);
  System_Message("Sending response to client.");
  
  if (size_send != response->size_resp) {
    *state |= (1 << ERROR); *error |= (1 << PSERR);
  }
  return;
}