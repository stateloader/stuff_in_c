#include <unistd.h>
#include "connect/connection.h"
#include "receive/receiver.h"
#include "response/responser.h"
#include "system/error.h"
#include "system/cstrings.h"
#include "controller.h"

static void process_relay(resp_t *response, recv_t *receive, cont_t *control) {
  
  if (control->status & (1 << ERROR)) return;

  response->protocol[TBIDX] = receive->protocol[TBIDX];
  response->protocol[ABIDX] = receive->protocol[ABIDX];
  response->protocol[EBIDX] = receive->protocol[EBIDX];

  if (response->protocol[TBIDX] & (0 << UNBIT)) {
    control->status |= (1 << ERROR); control->error |= (1 << RUERR);
  }
  if (response->protocol[ABIDX] & (0 << UNBIT)) {
    control->status |= (1 << ERROR); control->error |= (1 << RUERR);
  }
  if (response->protocol[EBIDX] & (0 << UNBIT)) {
    control->status |= (1 << ERROR); control->error |= (1 << RUERR);
  }

  response->size_recv = string_copy(response->received, receive->package, SBUFF);
  
  if (response->size_recv != receive->size_pack) {
    control->status |= (ERROR); control->error |= (1 << PCERR);
  }

  return;
}

static void state_receive(recv_t *receive, cont_t *control) {
  
  if (control->status & (1 << ERROR)) return;
  receive_driver(receive, &control->status, &control->error);

  return;
}

static void state_response(resp_t *response, cont_t *control) {
  
  if (control->status & (1 << ERROR)) return; 
  response_driver(response, &control->status, &control->error);

  return;
}

void control_driver(cont_t *control, serv_t *server) {

  socket_listen(server, &control->status, &control->error);
  socket_accept(server, &control->status, &control->error);

  recv_t receive =  {.client_sock_desc = server->client_sock_desc};
  resp_t response = {.client_sock_desc = server->client_sock_desc};
  
  state_receive(&receive, control);
  process_relay(&response, &receive, control);
  state_response(&response, control);
  close(server->client_sock_desc);


  error_driver(control->error);

  control->status ^= (1 << ALIVE);
}
