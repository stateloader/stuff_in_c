/*----------------------------------------------------------------------------------------------------------------RECEIVER

------------------------------------------------------------------------------------------------------------------------*/
#include "../connect/connection.h"
#include "models.h"
#include "receiver.h"

static void protocol_obtain(recv_t *receive, uint8_t *state, uint16_t *error)  {
/*A package on both client- and serverside should end with the PROTOCOL. If the received package has a lesser size than
 *'POFFS' or isn't nullterminated it's instantly invalid. Same is true if (in this case) the server has replied with the
 *VALID-bit cleared, meaning something went south when working with the client's request.*/

  if (receive->package[receive->size_pack - 1] != '\0') {
    *state |= (1 << ERROR); *error |= (1 << PTERR); return;
  }
  if (receive->size_pack < POFFS) {
    *state |= (1 << ERROR); *error |= (1 << RSERR); return;
  }
  receive->protocol[TBIDX] = receive->package[receive->size_pack - 4];
  receive->protocol[ABIDX] = receive->package[receive->size_pack - 3];
  receive->protocol[EBIDX] = receive->package[receive->size_pack - 2];

  if (receive->protocol[EBIDX] & (0 << VALID)) {
    *state |= (1 << ERROR); *error |= (1 << IVERR); return;
  }
  if (receive->protocol[TBIDX] & (0 << UNBIT)) {
    *state |= (1 << ERROR); *error |= (1 << PBERR);
  }
  if (receive->protocol[ABIDX] & (0 << UNBIT)) {
    *state |= (1 << ERROR); *error |= (1 << PBERR);
  }
  if (receive->protocol[EBIDX] & (0 << UNBIT)) {
    *state |= (1 << ERROR); *error |= (1 << PBERR);
  }
  return;
}

static void validate_rows(recv_t *receive, size_t dcount, uint8_t *state, uint16_t *error) {
 /*Here I'm fetching number of rows in the (current) dataset by dividing all delims found in the received package with the
  *constant (N of delimiters) attached to every row/entry/model. By mod the amount of delims found with fetched rows I'm
  *able to check nothing gone south as well.*/

  size_t amnt_delm = 0;

  for (size_t i = 0; i < receive->size_pack; i++)
    amnt_delm += (receive->package[i] == DELIM) ? 1 : 0;
  receive->amnt_rows = (amnt_delm / dcount);
  
  if (amnt_delm % receive->amnt_rows != 0) {
    *state |= (1 << ERROR); *error |= (1 << DCERR);
  }
  return;
}

static void validate_pull(recv_t *receive, uint8_t *state, uint16_t *error) {
/*Table out of (set) Table-bit will be created from received package.*/

  receive->size_pack -= POFFS;

  if (receive->protocol[TBIDX] & (1 << TMESG)) {
    validate_rows(receive, DMESG, state, error);
    receive->table_mesg = table_mesg_create(receive->package, receive->size_pack, receive->amnt_rows, state, error);
  }
  if (receive->protocol[TBIDX] & (1 << TDVCE)) {
    validate_rows(receive, DDVCE, state, error);
    receive->table_dvce = table_dvce_create(receive->package, receive->size_pack, receive->amnt_rows, state, error);
  }
  return;
}

static void validate_push(recv_t *receive) {
/*Given original table (write) request, a validation based on which TBIDX-bit set will be printed.*/

  if (receive->protocol[TBIDX] & (1 << TMESG))
    System_Message("Your message was successfully delivered.");

  if (receive->protocol[TBIDX] & (1 << TDVCE))
    System_Message("Your interaction with the device was successfully executed.");

  return;
}

void receive_driver(recv_t *receive, uint8_t *state, uint16_t *error) {

  receive->size_pack = recv(receive->sock_desc, receive->package, RBUFF, 0);

  protocol_obtain(receive, state, error);
  if (*state & (1 << ERROR)) return;

  int32_t route = (receive->protocol[EBIDX] & (1 << RWBIT)) ? 1 :  0;

  switch (route) {
  case 0:
    validate_pull(receive, state, error);
    break;
  case 1:
    validate_push(receive);
    break;
  default:
    *state |= (1 << ERROR); *error |= (1 << SDERR);
    return;
  }
  return;
}
