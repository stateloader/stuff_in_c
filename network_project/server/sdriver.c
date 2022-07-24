/*------------------------------------------------------------------------------------------------------------SERVER DRIVER
When the server has established connection with a client four states will be ran and they're quite straight forward where
most of the logic for a given task taking place inside various "drivers". If any error-flag being raised, the process going
to "fall down" to 'state_outcome' with immediate return-calls.                                                                        
/------------------------------------------------------------------------------------------------------------------------*/
#include "connect/connection.h"
#include "receive/receiver.h"
#include "response/responder.h"
#include "system/error.h"
#include "system/configs.h"
#include "system/cstrings.h"
#include "sdriver.h"

static void state_receive(dver_t *driver, recv_t *receive) {
/*Fetches received data from client inside the "driver".*/

  if (driver->status & (1 << ERROR)) return;
  receive_driver(receive, &driver->status, &driver->error);
  
  return;
}
                  
static void state_courier(dver_t *driver, resp_t *response, recv_t *receive) {
/*Before struct-variable 'response' taking over it needs to gain access to data stored among members in 'receive' which is
 *taking place in here.*/

  if (driver->status & (1 << ERROR)) return;

  response->protocol = receive->protocol;
  response->received = receive->package;
  response->size_recv = receive->size_pack;

  return;
}

static void state_respond(dver_t *driver, resp_t *response) {
/*Creates and send a response to client inside the "driver".*/

  if (driver->status & (1 << ERROR)) return;
  
  response_driver(response, &driver->status, &driver->error);

  return;
}

static void state_summary(dver_t *driver) {

  if (driver->status & (1 << ERROR))
    error_driver(&driver->status, &driver->error);
  close(driver->server.client_sock_desc);
}

void server_driver(dver_t *driver) {

  recv_t receive =  {.client_sock_desc = driver->server.client_sock_desc};
  resp_t response = {.client_sock_desc = driver->server.client_sock_desc};
  
  state_receive(driver, &receive);
  state_courier(driver, &response, &receive);
  state_respond(driver, &response);
  state_summary(driver);

  return;
}