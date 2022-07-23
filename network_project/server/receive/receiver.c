/*-----------------------------------------------------------------------------------------------------------------RECEIVER
                                                                                 
-------------------------------------------------------------------------------------------------------------------------*/

#include <sys/socket.h>
#include "receiver.h"

static void validate_recv(recv_t *receive, uint16_t *state, uint16_t *error) {
/*Validates received data.*/

  System_Message("Validating package.");

  if (receive->package[receive->size_pack - 1] != '\0') {
    *state |= (1 << ERROR); *error |= (1 << PTERR); return;
  }//received package isn't terminated.
  if (receive->size_pack < POFFS) {
    *state |= (1 << ERROR); *error |= (1 << PSERR); return;
  }//received package is of corrupted size.

  receive->protocol[TBIDX] = receive->package[receive->size_pack - 4];
  receive->protocol[ABIDX] = receive->package[receive->size_pack - 3];
  receive->protocol[EBIDX] = receive->package[receive->size_pack - 2];

  if (!(receive->protocol[EBIDX] & (1 << VALID))) {
    *state |= (1 << ERROR); *error |= (1 << PIERR);
  }//received package hasen't valid-flag set.
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

  receive->size_pack = recv(receive->client_sock_desc, receive->package, SBUFF, 0);
  System_Message("Package received from client.");
  validate_recv(receive, state, error);

  return;
}