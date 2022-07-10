/*-----------------------------------------------------------------------------------------------------------------RECEIVER
First leg of the (a) client's request starts with the receival. It happens here with some validation-checks.                                                                                       
-------------------------------------------------------------------------------------------------------------------------*/

#include <sys/socket.h>
#include "receiver.h"

static void validate_receival(recv_t *receive, uint16_t *state, uint16_t *error) {
/*A received package's last 4 bytes should be PROTOCOL. These being assigned to the receiver's protocol-member for easy
 *access during the errant.*/

  System_Message("Validating package.");

  if (receive->package[receive->size_pack - 1] != '\0') {
    *state |= (1 << ERROR); *error |= (1 << RTERR); return;
  }// Received package not nullterminated.
  if (receive->size_pack < POFFS) {
    *state |= (1 << ERROR); *error |= (1 << RSERR); return;
  }// Received package size lesser than ("mandatory") protocol-size.

  receive->protocol[TBIDX] = receive->package[receive->size_pack - 4];
  receive->protocol[ABIDX] = receive->package[receive->size_pack - 3];
  receive->protocol[EBIDX] = receive->package[receive->size_pack - 2];

  if (receive->protocol[TBIDX] & (0 << UNBIT)) {
    *state |= (1 << ERROR); *error |= (1 << RUERR);
  } if (receive->protocol[ABIDX] & (0 << UNBIT)) {
    *state |= (1 << ERROR); *error |= (1 << RUERR);
  } if (receive->protocol[EBIDX] & (0 << UNBIT)) {
    *state |= (1 << ERROR); *error |= (1 << RUERR);
  }// Most significant bit isn't set (equals corrupted protocol).
  return;
}

void receive_driver(recv_t *receive, uint16_t *state, uint16_t *error) {

  receive->size_pack = recv(receive->client_sock_desc, receive->package, SBUFF, 0);

  System_Message("Package received from client.");

  validate_receival(receive, state, error);
  return;
}