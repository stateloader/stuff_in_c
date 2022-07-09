/*---------------------------------------------------------------------------------------------------------------Controller
Macros implemented reg                                                                                                   
//-----------------------------------------------------------------------------------------------------------------------*/
#include "system/error.h"
#include "bitwise/bitengine.h"
#include "connect/connection.h"
#include "request/requester.h"
#include "command/commander.h"
#include "command/cstrings.h"
#include "command/scanner.h"
#include "receive/receiver.h"
#include "cdriver.h"

static void protocol_copy(uint8_t *dest, uint8_t *from) {
  dest[TBIDX] = from[TBIDX];
  dest[ABIDX] = from[ABIDX];
  dest[EBIDX] = from[EBIDX];
}

static void state_command(dver_t *driver) {

  if (driver->state & (1 << ERROR)) return;
  
  cmnd_t command = {0};
  command_driver(&command, &driver->state, &driver->error);
  protocol_copy(driver->protocol, command.protocol);
  return;
}

static void state_request(dver_t *driver) {
  
  if (driver->state & (1 << ERROR)) return; 

  reqt_t request = {.sock_desc = driver->client.sock_desc};
  protocol_copy(request.protocol, driver->protocol);
  request.size_user = string_copy(request.username, driver->client.username, SBUFF);
  request_driver(&request, &driver->state, &driver->error);

  return;
}

static void state_receive(dver_t *driver) {

  if (driver->state & (1 << ERROR)) return;

  recv_t receive = {.sock_desc = driver->client.sock_desc};
  receive_driver(&receive, &driver->state, &driver->error);
}

void client_driver(dver_t *driver) {
  
  state_command(driver);
  state_request(driver);
  state_receive(driver);

  error_driver(driver->state, driver->error);
}
