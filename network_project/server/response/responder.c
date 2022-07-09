/*-----------------------------------------------------------------------------------------------------------------RESPONSE
Macros implemented reg                                                                                                   
-------------------------------------------------------------------------------------------------------------------------*/

#include <sys/socket.h>
#include "../system/cstrings.h"
#include "reader.h"
#include "writer.h"
#include "responder.h"

static void protocol_attach(resp_t *response) {
/*Same drill as throughout the program both on the server and client side. PROTOCOL beeing attached at the end of the
 *response back to the client.*/

  response->response[response->size_resp - 4] = response->protocol[TBIDX];
  response->response[response->size_resp - 3] = response->protocol[ABIDX];
  response->response[response->size_resp - 2] = response->protocol[EBIDX];
  response->response[response->size_resp - 1] = '\0';

  return;
}

static void response_create(resp_t *response, uint16_t *state) {
/*Final "touch" in creating a response, PROTOCOL being attached, flags "not VALID" if any errors has accured which later
 *being dealt with on the client side.*/

  response->size_resp += POFFS;

  if (*state & (1 << ERROR))
    response->protocol[EBIDX] &= ~(1 << VALID);
  protocol_attach(response);

  return;
}

static void database_reader(resp_t *response, uint16_t *state, uint16_t *error) {
 /*Reader's protocol-member pointing at response-protocol. No need to*/

  read_t reader = {.size_cont = 0};
  reader.protocol = response->protocol;

  read_driver(&reader, state, error);
  response->size_resp = string_copy(response->response, reader.content, RBUFF) - 1;
  response_create(response, state);
  return;
}


static void database_writer(resp_t *response, uint16_t *state, uint16_t *error) {
 /*The Writer's protocol-member pointing at the response-protocol, its append-member at the received data which going to
  *(if everything goes well) be inserted to the (a) database.*/

  write_t writer = {.size_appd = response->size_recv};
  writer.protocol = response->protocol;
  writer.append = response->received;

  write_driver(&writer, state, error);
  response_create(response, state);

  return;
}

void response_driver(resp_t *response, uint16_t *state, uint16_t *error) {
/*If PROTOCOL sent from the client has its RWBIT set it means its a request for pushing/writing anything to the (a)
 *database while the opposite means read/pull.*/

  System_Message("Creates response.");

  int32_t route = (response->protocol[EBIDX] & (1 << RWBIT)) ? 1 : 0;

  switch (route) {
  case 0:
    database_reader(response, state, error);
    break;
  case 1:
    database_writer(response, state, error);
    break;
  default:
    *state |= (1 << ERROR); *error |= (1 << SWERR);
    return;
  }
  
  size_t size_send = send(response->client_sock_desc, response->response, response->size_resp, 0);
  if (size_send != response->size_resp) {
    *state |= (1 << ERROR); *error |= (1 << RCERR);
  }
  return;
}