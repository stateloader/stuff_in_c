/*------------------------------------------------------------------------------------------------------------SERVER DRIVER
I'd mwih ease                                                                              
/------------------------------------------------------------------------------------------------------------------------*/
#include "connect/connection.h"
#include "receive/receiver.h"
#include "response/responder.h"
#include "system/error.h"
#include "system/configs.h"
#include "system/cstrings.h"
#include "sdriver.h"

static void state_receive(dver_t *driver, recv_t *receive) {

  if (driver->status & (1 << ERROR)) return;
  System_Message("state receive.");

  receive_driver(receive, &driver->status, &driver->error);

  return;
}
                  
static void state_courier(dver_t *driver, resp_t *response, recv_t *receive) {

  if (driver->status & (1 << ERROR)) return;
  System_Message("state courier.");

  response->protocol = receive->protocol;
  response->received = receive->package;
  response->size_recv = receive->size_pack;

  return;
}

static void state_respond(dver_t *driver, resp_t *response) {

  if (driver->status & (1 << ERROR)) return;
  System_Message("state respond.");
  
  response_driver(response, &driver->status, &driver->error);

  return;
}

static void state_outcome(dver_t *driver) {

  error_driver(driver->status, driver->error);
  driver->error &= ~(1 << ERROR);
  close(driver->server.client_sock_desc);
}

void server_driver(dver_t *driver) {

  recv_t receive =  {.client_sock_desc = driver->server.client_sock_desc};
  resp_t response = {.client_sock_desc = driver->server.client_sock_desc};
  
  state_receive(driver, &receive);
  state_courier(driver, &response, &receive);
  state_respond(driver, &response);
  
  state_outcome(driver);
}