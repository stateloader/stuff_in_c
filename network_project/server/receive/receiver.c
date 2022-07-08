
#include <sys/socket.h>
#include "receiver.h"

static void protocol_obtain(recv_t *receive, uint8_t *state, uint16_t *error) {

  receive->protocol[TBIDX] = receive->package[receive->size_pack - 4];
  receive->protocol[ABIDX] = receive->package[receive->size_pack - 3];
  receive->protocol[EBIDX] = receive->package[receive->size_pack - 2];
}

void receive_driver(recv_t *receive, uint16_t *state, uint16_t *error) {

  receive->size_pack = recv(receive->client_sock_desc, receive->package, SBUFF, 0);
  System_Message(receive->package);

  return;
}