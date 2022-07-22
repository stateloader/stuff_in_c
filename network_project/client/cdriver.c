/*------------------------------------------------------------------------------------------------------------CLIENT DRIVER
When connected, the (a) session going to run through 4 states. During state 'command', client's creating a request which
being "encoded" into a package sent to the server in state 'request' before receiving server response in state 'reponse'.
If any error accurs during the process the logic will just "fall through" with immideate return-calls down to <outcome>.
//-----------------------------------------------------------------------------------------------------------------------*/

#include "system/error.h"
#include "bitwise/bitengine.h"
#include "connect/connection.h"
#include "request/requester.h"
#include "command/commander.h"
#include "system/cstrings.h"
#include "system/scanner.h"
#include "receive/publish.h"
#include "receive/receiver.h"
#include "cdriver.h"

static void protocol_copy(uint8_t *dest, uint8_t *from) {
  dest[TBIDX] = from[TBIDX];
  dest[ABIDX] = from[ABIDX];
  dest[EBIDX] = from[EBIDX];
}

static void state_command(dver_t *driver) {
/*Command state, see COMMAND MODULE*/

  if (driver->state & (1 << ERROR)) return;
  driver->state |= (1 << SCOMM);

  command_driver(driver->protocol);

  return;
}

static void state_request(dver_t *driver) {
/*Request state, see REQUEST MODULE.*/

  if (driver->state & (1 << ERROR)) return;

  driver->state &= ~(1 << SCOMM);
  driver->state |= (1 << SREQT);

  reqt_t request = {.sock_desc = driver->client.sock_desc};

  protocol_copy(request.protocol, driver->protocol);
  request.size_user = string_copy(request.username, driver->client.username, SBUFF);

  request_driver(&request, &driver->state, &driver->error);

  return;
}

static void state_receive(dver_t *driver) {
/*Request state, see RECEIVE MODULE.*/

  if (driver->state & (1 << ERROR)) return;

  driver->state &= ~(1 << SREQT);
  driver->state |= (1 << SRECV);

  recv_t receive = {.sock_desc = driver->client.sock_desc};
  
  receive_driver(&receive, &driver->state, &driver->error);
  publish_driver(&receive, &driver->state, &driver->error);

  return;
}

static void state_outcome(dver_t *driver) {
/*Outcome state, checks for errors and asks for more.*/

  error_driver(driver->state, driver->error);
  if (driver->state & (1 << ERROR)) return;

  driver->state &= ~(1 << SREQT);
  driver->state &= ~(1 << SCONN);
}

void client_driver(dver_t *driver) {

  state_command(driver);
  state_request(driver);
  state_receive(driver);
  state_outcome(driver);
}