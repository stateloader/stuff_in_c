/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                   RECIEVE
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include "socket.h"
#include "models.h"
#include "receive.h"
//----------------------------------------------------------------------------------------------------CREATE MESSAGE TABLE
static int8_t count_rows(recv_t *receive) {
  for (int32_t i = 0; i < receive->size_recv; i++)
    receive->meta.count_delm += (receive->recv[i] == DELIM) ? 1 : 0;
  receive->meta.count_rows = (receive->meta.count_delm / receive->meta.entry_delim);
  return SUCC;
}

static int8_t distributor_mesg(recv_t *receive) {

  int32_t mem = 0, idx = 0, row = 0;

  for (int32_t i = 0; i < receive->size_recv; i++) {   // if  i == size_resc - 1 "ok"
    char byte = receive->recv[i];

    switch(mem) { 
    case 0:
    if (byte != DELIM) {
      receive->table_mesg[row].user[idx] = byte;
      idx++;
    } else {
      receive->table_mesg[row].user[idx] = '\0';
      mem++, idx = 0;
      System_Message( receive->table_mesg[row].user);
    }
    break;
    case 1:
    if (byte != DELIM) {
      receive->table_mesg[row].datm[idx] = byte;
      idx++;
    } else {
      receive->table_mesg[row].datm[idx] = '\0';
      mem++, idx = 0;
    }
    break;
    case 2:
    if (byte != DELIM) {
      receive->table_mesg[row].topc[idx] = byte;
      idx++;
    } else {
      receive->table_mesg[row].topc[idx] = '\0';
      mem++, idx = 0;
    }
    break;
    case 3:
    if (byte != DELIM) {
      receive->table_mesg[row].mesg[idx] = byte;
      idx++;
    } else {
      receive->table_mesg[row].mesg[idx] = '\0';
      mem = 0, idx = 0, row++;
    }
    break;
    default:
    System_Message("oh noes");
    return QUIT;
    }
  }

  return SUCC;
}

static int8_t link_table_mesg(recv_t *receive) {

  count_rows(receive);
  receive->table_mesg = malloc(sizeof(mmod_t) * receive->meta.count_rows);
  return distributor_mesg(receive);
}
//----------------------------------------------------------------------------------------------------CREATE DEVICE TABLE
static int8_t link_table_dvce(recv_t *receive) {

  System_Message("Inside construct dvce");
  return SUCC;
}

static recv_item recv_items[] = {
  {TMESG, DMSGE, link_table_mesg},
  {TDVCE, DDVCE, link_table_dvce}
};

int8_t receive_driver(recv_t *receive) {
  for (size_t i = 0; i < ARRAY_SIZE(recv_items); i++) {
    if (receive->protocol[TINDX] & (1 << recv_items[i].table)) {
      receive->meta.entry_delim = recv_items[i].delim;
      return recv_items[i].func(receive);
    }
  }
  System_Message("Error while creating table");
  return FAIL;
}