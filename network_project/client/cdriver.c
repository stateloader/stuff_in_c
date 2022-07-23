/*------------------------------------------------------------------------------------------------------------CLIENT DRIVER
When connected, the (a) session going to run through 4 states shown and described below. If any error accurs during this
process, flags will be raised whereafter the logic from that point forward will "fall through" down to 'state_outcome'
by immideate return-calls.
//-----------------------------------------------------------------------------------------------------------------------*/

#include "system/error.h"
#include "connect/connection.h"
#include "request/requester.h"
#include "command/commander.h"
#include "system/cstrings.h"
#include "system/scanner.h"
#include "receive/receiver.h"
#include "cdriver.h"

static void state_command(dver_t *driver) {
/*Struct variable 'driver' throws member 'protocol' into the 'command_driver' where this 3 byte-array being assigned based
 *on userinput. When assigned, it becomes 'the very' PROTOCOL and governs how the program behaves in upcoming state both on
 *client and server-side. SEE COMMAND MODULE.*/

  if (driver->state & (1 << ERROR)) return;

  driver->state |= (1 << SCOMM);
  command_driver(driver->protocol);

  return;
}

static void state_request(dver_t *driver) {
/*Struct-variable 'request' will assign 'sock_desc' and 'size_user' from 'driver/client' while pointing at its
 *'protocol' and 'username'-array, making this data available inside the 'request_driver'. SEE REQUEST MODULE.*/

  if (driver->state & (1 << ERROR)) return;

  driver->state &= ~(1 << SCOMM);
  driver->state |= (1 << SREQT);

  reqt_t request = {
    .sock_desc = driver->client.sock_desc, .protocol = driver->protocol,
    .size_user = driver->client.size_user, .username = driver->client.username
  };
  request_driver(&request, &driver->state, &driver->error);

  return;
}

static void state_receive(dver_t *driver) {
/*Struct-variable 'receive' going to be used while crunching the server's response. SEE RECEIVE MODULE.*/

  if (driver->state & (1 << ERROR)) return;

  driver->state &= ~(1 << SREQT);
  driver->state |= (1 << SRECV);

  recv_t receive = {.sock_desc = driver->client.sock_desc};
  receive_driver(&receive, &driver->state, &driver->error);

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