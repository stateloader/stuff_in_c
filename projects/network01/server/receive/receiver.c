/*-----------------------------------------------------------------------------------------------------------------RECEIVER
Source-file that governs all receive-logic from its "driver".                                               
-------------------------------------------------------------------------------------------------------------------------*/

#include <sys/socket.h>
#include "receiver.h"

static void validate_recv(recv_t *receive, uint16_t *state, uint16_t *error) {
/*Validates received data and assigns PROTOCOL out of the last bytes. If the received data isn't terminated, or is lesser
 *than POFFS in size, something went horrible and the func will call return immediately after the error-flags is set.*/

  System_Message("validating package.");

  if (receive->package[receive->size_pack - 1] != '\0') {
    *state |= (1 << ERROR); *error |= (1 << PTERR); return;
  }//received package isn't terminated.
  if (receive->size_pack < POFFS) {
    *state |= (1 << ERROR); *error |= (1 << PSERR); return;
  }//received package is of corrupted size.

  receive->protocol[TBIDX] = receive->package[receive->size_pack - 4];
  receive->protocol[ABIDX] = receive->package[receive->size_pack - 3];
  receive->protocol[EBIDX] = receive->package[receive->size_pack - 2];
  
  if (!(receive->protocol[TBIDX] & (1 << MSBIT))) {
    *state |= (1 << ERROR); *error |= (1 << PBERR);
  }//received PROTOCOL corrupted.
  if (!(receive->protocol[ABIDX] & (1 << MSBIT))) {
    *state |= (1 << ERROR); *error |= (1 << PBERR);
  }//received PROTOCOL corrupted.
  if (!(receive->protocol[EBIDX] & (1 << MSBIT))) {
    *state |= (1 << ERROR); *error |= (1 << PBERR);
  }//received PROTOCOL corrupted.

  return;
}

void receive_driver(recv_t *receive, uint16_t *state, uint16_t *error) {
/*Assigns received data to members of struct-variable 'receive' and validates its content.*/

  receive->size_pack = recv(receive->client_sock_desc, receive->package, SBUFF, 0);
  System_Message("package received from client.");

  validate_recv(receive, state, error);
  
  return;
}
