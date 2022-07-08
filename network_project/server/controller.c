#include <unistd.h>
#include "connect/connection.h"
#include "receive/receiver.h"
#include "response/responser.h"
#include "system/error.h"
#include "controller.h"

static void state_receive(serv_t *server, cont_t *control) {

  recv_t receive = {.client_sock_desc = server->client_sock_desc};
  receive_driver(&receive, &control->status, &control->error);
}

void control_driver(cont_t *control, serv_t *server) {

  socket_listen(server, &control->status, &control->error);
  socket_accept(server, &control->status, &control->error);

  state_receive(server, control);

  close(server->client_sock_desc);
  control->status ^= (1 << ALIVE);
}
