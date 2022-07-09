
#include <sys/socket.h>
#include "receiver.h"

static void package_obtain(recv_t *receive, uint16_t *state, uint16_t *error) {
/*A received package 4 last byttes should be PROTOCOL which being being assigned to the reciever. However, if
 *the package is lesser than POFFS or not null-terminated an error flag is raised before an instant return.*/

  if (receive->package[receive->size_pack - 1] != '\0') {
    *state |= (1 << ERROR); *error |= (1 << RTERR); return;
  }
  if (receive->size_pack < POFFS) {
    *state |= (1 << ERROR); *error |= (1 << RSERR); return;
  }
  
  receive->protocol[TBIDX] = receive->package[receive->size_pack - 4];
  receive->protocol[ABIDX] = receive->package[receive->size_pack - 3];
  receive->protocol[EBIDX] = receive->package[receive->size_pack - 2];

  if (receive->protocol[TBIDX] & (0 << UNBIT)) {
    *state |= (1 << ERROR); *error |= (1 << RUERR);
  }
  if (receive->protocol[ABIDX] & (0 << UNBIT)) {
    *state |= (1 << ERROR); *error |= (1 << RUERR);
  }
  if (receive->protocol[EBIDX] & (0 << UNBIT)) {
    *state |= (1 << ERROR); *error |= (1 << RUERR);
  }
  return;
}

void receive_driver(recv_t *receive, uint16_t *state, uint16_t *error) {
  System_Message("Reading package.");
  
  receive->size_pack = recv(receive->client_sock_desc, receive->package, SBUFF, 0);
  package_obtain(receive, state, error);

  return;
}