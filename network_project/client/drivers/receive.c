/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                  Response
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include "socket.h"
#include "models.h"
#include "receive.h"
//----------------------------------------------------------------------------------------------------CREATE MESSAGE TABLE
static void distributor_mesg(recv_t *receive) {
/*
  for (int32_t i = 0; i < receive->count_rows; i++)
    receive->table_mesg[i].id = i;
*/
  int32_t mem = 0, idx = 0, row = 0;

  for (int32_t i = 0; i < receive->size_recv; i++) {
    char byte = receive->recv[i];

    switch(mem) { 
    case 0:
    if (byte != DELIM) {
      receive->table_mesg[row].set = byte;
      idx++;
    } else {
      receive->table_mesg[row].set = '\0';
      mem++, idx = 0;
    }
    break;
    case 1:
    if (byte != DELIM) {
      receive->table_mesg[row].user[idx] = byte;
      idx++;
    } else {
      receive->table_mesg[row].user[idx] = '\0';
      mem++, idx = 0;
    }
    break;
    case 2:
    if (byte != DELIM) {
      receive->table_mesg[row].datm[idx] = byte;
      idx++;
    } else {
      receive->table_mesg[row].datm[idx] = '\0';
      mem++, idx = 0;
    }
    break;
    case 3:
    if (byte != DELIM) {
      receive->table_mesg[row].topc[idx] = byte;
      idx++;
    } else {
      receive->table_mesg[row].topc[idx] = '\0';
      mem++, idx = 0;
    }
    break;
    case 4:
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
    }
  }
  return;
}

static void table_setup_mesg(recv_t *receive) {
//receives all message-data in an entire string from server's db and distributes it among model 'mesg'.

  for (int32_t i = 0; i < receive->size_recv; i++)
    receive->count_delm += (receive->recv[i] == DELIM) ? 1 : 0;
  receive->count_rows = (receive->count_delm / receive->entry_delim);

  receive->table_mesg =  malloc(sizeof(mmod_t) * receive->count_rows);
  distributor_mesg(receive);
  return;
}
//----------------------------------------------------------------------------------------------------CREATE DEVICE TABLE
static void table_setup_dvce(recv_t *receive) {
//receives all device-data in an entire string from server's db and distributes it among model 'dvce'.
  System_Message("Inside construct dvce");
}

static recv_item recv_items[] = {
  {TMESG, DMSGE, table_setup_mesg},
  {TDVCE, DDVCE, table_setup_dvce}
};

void receive_driver(recv_t *receive) {

  for (size_t i = 0; i < ARRAY_SIZE(recv_items); i++) {
    if (receive->protocol[TINDX] & (1 << recv_items[i].table)) {
      receive->entry_delim = recv_items[i].delim;
      return recv_items[i].func(receive);
    }
  }
  System_Message("Error while creating table");
  receive->status = 0;
}