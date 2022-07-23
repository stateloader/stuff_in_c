/*----------------------------------------------------------------------------------------------------------------RECEIVER

------------------------------------------------------------------------------------------------------------------------*/
#include "../connect/connection.h"
#include "models.h"
#include "publish.h"
#include "receiver.h"

static void validate_recv(recv_t *receive, uint8_t *state, uint16_t *error)  {
/*Validates received data.*/
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
  //assigns received protocol. 

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

static void validate_rows(recv_t *receive, size_t dcount, uint8_t *state, uint16_t *error) {
 /*I'm fetching number of rows in the (current) dataset by dividing all delims found in the received package with the
  *constant (N of delimiters) attached to every row/entry/model. By mod the amount of delims found with fetched rows
  *I'm able to check nothing gone south in the process as well.*/

  size_t amnt_delm = 0;

  for (size_t i = 0; i < receive->size_pack; i++)
    amnt_delm += (receive->package[i] == DELIM) ? 1 : 0;
  receive->amnt_rows = (amnt_delm / dcount);
  
  if (amnt_delm % receive->amnt_rows != 0) {
    *state |= (1 << ERROR); *error |= (1 << PDERR);
  }//delimiter-count is corrupted.

  return;
}

static void received_pull(recv_t *receive, uint8_t *state, uint16_t *error) {
/*Data received from a request of type 'pull' (an entire database atm) being organised into tables.*/ 

  receive->size_pack -= POFFS;

  switch(receive->protocol[TBIDX]) {
  case RECV_MESG:
    validate_rows(receive, DMESG, state, error);
    receive->table_mesg = table_mesg_create(receive->package, receive->size_pack, receive->amnt_rows, state, error);
  break;
  case RECV_DVCE:
    validate_rows(receive, DDVCE, state, error);
    receive->table_dvce = table_dvce_create(receive->package, receive->size_pack, receive->amnt_rows, state, error);
  break;
  default:
    *state |= (1 << ERROR); *error |= (1 << SDERR);
    return;
  }
  
  publish_driver(receive, state, error);

  return;
}

static void received_push(recv_t *receive, uint8_t *state, uint16_t *error)  {
/*Data received from a request of type 'push' just "decoding" the PROTOCOL for printing validations.*/ 

  switch(receive->protocol[TBIDX]) {
  case RECV_MESG:
    System_Message("your message was successfully delivered.");
  break;
  case RECV_DVCE:
    System_Message("your interaction with the device was successfully executed.");
  break;
  default:
    *state |= (1 << ERROR); *error |= (1 << SDERR);
  }

  return;
}

void receive_driver(recv_t *receive, uint8_t *state, uint16_t *error) {

  receive->size_pack = recv(receive->sock_desc, receive->package, RBUFF, 0);
  validate_recv(receive, state, error);

  if (*state & (1 << ERROR)) return;

  int32_t receive_route = (receive->protocol[EBIDX] & (1 << RWBIT)) ? 1 :  0;

  switch (receive_route) {
  case 0:
    received_pull(receive, state, error);
    break;
  case 1:
    received_push(receive, state, error);
    break;
  default:
    *state |= (1 << ERROR); *error |= (1 << SDERR);
  }

  return;
}
