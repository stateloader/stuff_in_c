/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                  Response
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include "socket.h"
#include "models.h"
#include "receive.h"

//----------------------------------------------------------------------------------------------------CREATE MESSAGE TABLE

static void table_setup_mesg(recv_t *receive) {
//receives all message-data in an entire string from server's db and distributes it among model 'mesg'.

  for (int32_t i = 0; i < receive->size_recv; i++)
    receive->count_delm += (receive->recv[i] == DELIM) ? 1 : 0;
  receive->count_rows = (receive->count_delm / receive->this_delim);

  receive->table_mesg =  malloc(sizeof(mmod_t) * receive->count_rows);
  distributor_mesg(receive);
  free(receive->table_mesg);

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
      receive->this_delim = recv_items[i].delim;
      return recv_items[i].func(receive);
    }
  }
  System_Message("Error while creating table");
  receive->status = 0;
}