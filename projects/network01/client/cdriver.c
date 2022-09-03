/*------------------------------------------------------------------------------------CLIENT DRIVER
When/if connected, the program going to run through three states.

In 'state_command' the user choose a request which being assembled and sent to the server from
'state_request' before the response is catched in 'state_receive'.
-------------------------------------------------------------------------------------------------*/
#include <unistd.h>
#include "connect/connect.h"
#include "request/request.h"
#include "command/commander.h"
#include "jackIO/cstrings.h"
#include "jackIO/scanner.h"
#include "receive/receive.h"
#include "cdriver.h"

static void state_command(driver_t *driver) {
/*Sets SCOMM (command-state bit) so the system know where we are in the process before the user
 *choose a command/task/errant inside 'command_driver'.*/
 
  driver->state |= (1 << SCOMM);
  command_driver(driver->protocol);
  return;
}

static void state_request(driver_t *driver) {
/*Clears the SCOMM bit and sets SREQT (request-state bit). reqt_t struct-variable 'request' is
 *declared before relevant data for the request-process is assigned/referenced to it's members.
 *'request' then being pointed to from the request_driver.*/
  
  driver->state &= ~(1 << SCOMM); driver->state |= (1 << SREQT);
  
  reqt_t request = {
    .sock_desc = driver->client.sock_desc,.protocol = driver->protocol,
    .size_user = driver->client.size_user,.username = driver->client.username
  };
  request_driver(&request);
  return;
}

static void state_receive(driver_t *driver) {
/*Clears the SREQT-bit and sets SRECV (receive-state bit). recv_t struct-variable 'receive' is
 *declared and relevant data för the receive-process is assigned/referenced to it's members.
 *'receive' then being pointed to from the receive-driver.*/

  driver->state &= ~(1 << SREQT); driver->state |= (1 << SRECV);
  
  recv_t receive = {.sock_desc = driver->client.sock_desc};
  receive_driver(&receive);
  return;
}

void client_driver(driver_t *driver) {
  
  state_command(driver);
  state_request(driver);
  state_receive(driver);
  
  close(driver->client.sock_desc);
}
