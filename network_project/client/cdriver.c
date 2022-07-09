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

static size_t content_imitate(char *dest, char *from, size_t size_from) {
 
 size_t size_dest = string_copy(dest, from, size_from + 1);
 return size_dest;
}

static void state_connect(conn_t *connect, dver_t *driver) {

  connect_driver(connect, &driver->state, &driver->error);
  if (driver->state & (1 << ERROR)) return;

  driver->sock_desc = connect->sock_desc;
}

static void state_command(cmnd_t *command, dver_t *driver) {
  
  if (driver->state & (1 << ERROR)) return;

  command_driver(command, &driver->state, &driver->error);
  driver->protocol = command->protocol;
}

static void state_request(reqt_t *request, dver_t *driver) {
  
  if (driver->state & (1 << ERROR)) return; 

  request->protocol = driver->protocol;
  request->size_user = content_imitate(request->username, driver->username, driver->size_user);

  request_driver(request, &driver->state, &driver->error);
  package_send(driver->sock_desc, request->package, request->size_pack,  &driver->state,  &driver->error);
}

static void state_receive(recv_t *receive, dver_t *driver) {

  if (driver->state & (1 << ERROR)) return;
  
  receive->size_pack = package_recv(driver->sock_desc, receive->package, &driver->state,  &driver->error);
  receive_driver(receive, &driver->state, &driver->error);
}

void client_driver(dver_t *driver) {

  static int test = 0;

  conn_t connect = {0};
  cmnd_t command = {0};
  reqt_t request = {0};
  recv_t receive = {0};

  state_connect(&connect, driver);
  state_command(&command, driver);
  state_request(&request, driver);
  //state_receive(&receive, control);

  if (driver->state & (1 << ERROR))
    error_driver(driver->error);

  test++;
  if (test == 2)
    driver->state ^= (1 << ALIVE);
}
