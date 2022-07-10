/*---------------------------------------------------------------------------------------------------------------Controller
info info info
//-----------------------------------------------------------------------------------------------------------------------*/
#include "system/error.h"
#include "bitwise/bitengine.h"
#include "connect/connection.h"
#include "request/requester.h"
#include "command/commander.h"
#include "system/cstrings.h"
#include "system/scanner.h"
#include "receive/receiver.h"
#include "cdriver.h"

#define SSUCC 0xF

static void protocol_copy(uint8_t *dest, uint8_t *from) {
  dest[TBIDX] = from[TBIDX];
  dest[ABIDX] = from[ABIDX];
  dest[EBIDX] = from[EBIDX];
}

static void state_command(dver_t *driver) {

  if (driver->state & (1 << ERROR)) return;
  
  cmnd_t command = {0};
  command_driver(&command);
  protocol_copy(driver->protocol, command.protocol);
  return;
}

static void state_request(dver_t *driver) {
  
  if (driver->state & (1 << ERROR)) return;
  driver->state |= (1 << SCOMM);

  reqt_t request = {.sock_desc = driver->client.sock_desc};
  protocol_copy(request.protocol, driver->protocol);
  request.size_user = string_copy(request.username, driver->client.username, SBUFF);
  request_driver(&request, &driver->state, &driver->error);

  return;
}

static void state_receive(dver_t *driver) {
  if (driver->state & (1 << ERROR)) return;
  driver->state |= (1 << SREQT);

  recv_t receive = {.sock_desc = driver->client.sock_desc};
  receive_driver(&receive, &driver->state, &driver->error);
}

static void state_outcome(dver_t *driver) {
  if (driver->state & (1 << ERROR)) return;
  driver->state |= (1 << SRECV);

  if (driver->state == SSUCC)
    System_Message("session full pott");
}


void client_driver(dver_t *driver) {
  
  state_command(driver);
  state_request(driver);
  state_receive(driver);
  state_outcome(driver);

  error_driver(driver->state, driver->error);
}
