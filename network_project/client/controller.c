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
#include "controller.h"

static size_t content_imitate(char *dest, char *from, size_t size_from) {
 
 size_t size_dest = string_copy(dest, from, size_from + 1);
 return size_dest;
}

static void state_connect(conn_t *connect, cont_t *control) {

  connect_driver(connect, &control->state, &control->error);
  error_driver(control->error, "state connect.");
  if (control->state & (1 << ERROR)) return;

  control->sock_desc = connect->sock_desc;
  control->size_user = content_imitate(control->username, connect->username, connect->size_user);
  control->size_pass = content_imitate(control->password, connect->password, connect->size_pass);
}

static void state_command(cmnd_t *command, cont_t *control) {
  
  if (control->state & (1 << ERROR)) return;

  command_driver(command, &control->state, &control->error);
  error_driver(control->error, "state command.");

  control->protocol = command->protocol;
}

static void state_request(reqt_t *request, cont_t *control) {
  
  if (control->state & (1 << ERROR)) return; 

  request->protocol = control->protocol;
  request->size_user = content_imitate(request->username, control->username, control->size_user);

  request_driver(request, &control->state, &control->error);
  package_send(control->sock_desc, request->package, request->size_pack,  &control->state,  &control->error);
  error_driver(control->error, "state request.");
}

static void state_receive(recv_t *receive, cont_t *control) {

  if (control->state & (1 << ERROR)) return;
  
  receive->size_pack = package_recv(control->sock_desc, receive->package, &control->state,  &control->error);
  receive_driver(receive, &control->state, &control->error);
  error_driver(control->error, "state receive");
}

void control_driver(cont_t *control) {

  conn_t connect = {0};
  cmnd_t command = {0};
  reqt_t request = {0};
  recv_t receive = {0};

  state_connect(&connect, control);
  state_command(&command, control);
  state_request(&request, control);
  //state_receive(&receive, control);
  
  control->state ^= (1 << ALIVE);
}
