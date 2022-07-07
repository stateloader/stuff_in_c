/*-----------------------------------------------------------------------------------------------------------------RECEIVER
Logic dealing with creation of device requests; send (interact with device) or read historical records from the server.
Logic dealing with creation of message-requests; send to or read historical records from the server.
------------------------------------------------------------------------------------------------------------------------*/
#include "models.h"
#include "receiver.h"

static void protocol_obtain(recv_t *receive, uint8_t *state, uint16_t *error)  {
/*Assigns the T, A and S Byte to the protocol from the package*/

  if (receive->package[receive->size_pack - 1] != '\0') {
    *state |= (1 << ERROR); *error |= (1 << PTERR); return;
  } // If package isn't nullterminated, leave at once.

  receive->protocol[TBIDX] = receive->package[receive->size_pack - 4];
  receive->protocol[ABIDX] = receive->package[receive->size_pack - 3];
  receive->protocol[EBIDX] = receive->package[receive->size_pack - 2];

  if (receive->protocol[EBIDX] & (0 << VALID)) {
    *state |= (1 << ERROR); *error |= (1 << IVERR); return;
  } // If server found request invalid, leave at once.

  if (receive->protocol[TBIDX] & (0 << UNBIT)) {
    *state |= (1 << ERROR); *error |= (1 << PBERR);
  }
  if (receive->protocol[ABIDX] & (0 << UNBIT)) {
    *state |= (1 << ERROR); *error |= (1 << PBERR);
  }
  if (receive->protocol[EBIDX] & (0 << UNBIT)) {
    *state |= (1 << ERROR); *error |= (1 << PBERR);
  }
}

static void fetch_rows(recv_t *receive, uint8_t *state, uint16_t *error) {
 /*I'm able to fetch number of rows in the (current) dataset by dividing all delims found in the (current) dataset
 *with the constant (N of delimiters) attached to every row/entry/model. By mod the amount of delims found with
 *fetched rows I'm then able to check nothing gone south.*/

  for (size_t i = 0; i < receive->size_pack; i++)
    receive->amnt_delm += (receive->package[i] == DELIM) ? 1 : 0;
  receive->amnt_rows = (receive->amnt_delm / receive->tabl_delm);

  if (receive->amnt_delm % receive->amnt_rows != 0) {
    *state |= (1 << ERROR); *error |= (1 << DCERR);
  }
  return;
}

static void fetch_data(recv_t *receive, uint8_t *state, uint16_t *error) {

  if (receive->protocol[TBIDX] & (1 << TMESG)) {
    receive->table_mesg = table_mesg_create(
      receive->package, receive->size_pack, receive->amnt_rows,
      state, error);

  } else if (receive->protocol[TBIDX] & (1 << TDVCE)) {
    receive->table_dvce = table_dvce_create(
      receive->package, receive->size_pack, receive->amnt_rows,
      state, error);

  } else {
    *state |= (1 << ERROR); *error |= (1 << IIERR);
  }
  return;
}

static void print_resp(recv_t *receive, uint8_t *state, uint16_t *error) {

  if (receive->protocol[TBIDX] & (1 << TMESG)) {
    System_Message("Your message was successfully delivered.");

  } else if (receive->protocol[TBIDX] & (1 << TDVCE)) {
    System_Message("Your interaction with the device is executed.");

  } else {
    *state |= (1 << ERROR); *error |= (1 << IIERR);
  }
  return;
}

void receive_driver(recv_t *receive, uint8_t *state, uint16_t *error) {

  protocol_obtain(receive, state, error);
  if (*state & (1 << ERROR)) return;

  int32_t route = (receive->protocol[EBIDX] & (1 << RWBIT)) ? 1 :  0;
  receive->size_pack -= POFFS;

  switch (route) {
  case 0:
    print_resp(receive, state, error);
    break;

  case 1:
    fetch_rows(receive, state, error);
    if (*state & (1 << ERROR)) return;
    fetch_data(receive, state, error);
    break;

  default:
    *state |= (1 << ERROR); *error |= (1 << SDERR);
    return;
  }
  return;
}
