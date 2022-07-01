/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                   RECIEVE
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include "models.h"
#include "receive.h"

static int8_t count_rows(recv_t *receive) {
//desc
  for (int32_t i = 0; i < receive->size_recv; i++)
    receive->meta.count_delm += (receive->recv[i] == DELIM) ? 1 : 0;
  receive->meta.count_rows = (receive->meta.count_delm / receive->meta.entry_delim);
  return SUCC;
}

static int8_t create_table_mesg(recv_t *receive) {
/*First I made a generic, recursive solution of some sort but it turned out to be (way) to messy. Instead, every table,
 *current or later added, going to be hardcoded after the principle below.
 */

  count_rows(receive);
  receive->table_mesg = malloc(sizeof(mmod_t) * receive->meta.count_rows);

  int32_t mem = 0, idx = 0, row = 0;

  for (int32_t i = 0; i < receive->size_recv; i++) {
    char byte = receive->recv[i];

    switch(mem) {
    case 0:
    if (byte != DELIM) {
      receive->table_mesg[row].user[idx] = byte;
      idx++;
    } else {
      receive->table_mesg[row].user[idx] = '\0';
      mem++, idx = 0;
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
      receive->table_mesg->id = row;
      mem = 0, idx = 0, row++;
    }
    break;
    default:
      Message_Info("oh noes");
      return EXIT;
    }
  }
  if (receive->table_mesg) free(receive->table_mesg);
  return SUCC;
}

static int8_t create_table_dvce(recv_t *receive) {

  count_rows(receive);
  receive->table_dvce = malloc(sizeof(dmod_t) * receive->meta.count_rows);

  int32_t mem = 0, idx = 0, row = 0;

  for (int32_t i = 0; i < receive->size_recv; i++) {
    char byte = receive->recv[i];

    switch(mem) {
    case 0:
    if (byte != DELIM) {
      receive->table_dvce[row].user[idx] = byte;
      idx++;
    } else {
      receive->table_dvce[row].user[idx] = '\0';
      mem++, idx = 0;
    }
    break;
    case 1:
    if (byte != DELIM) {
      receive->table_dvce[row].datm[idx] = byte;
      idx++;
    } else {
      receive->table_dvce[row].datm[idx] = '\0';
      mem++, idx = 0;
    }
    break;
    case 2:
    if (byte != DELIM) {
      receive->table_dvce[row].init[idx] = byte;
      idx++;
    } else {
      receive->table_dvce[row].init[idx] = '\0';
      receive->table_dvce->id = row;
      mem = 0, idx = 0, row++;
    }
    break;
    default:
      Message_Info("oh noes");
      return EXIT;
    }
  }
  if (receive->table_dvce) free(receive->table_dvce);
  return SUCC;
}

static recv_item recv_items[] = {
  {TMESG, DMSGE, create_table_mesg},
  {TDVCE, DDVCE, create_table_dvce}
};

static int8_t init_table(recv_t *receive) {

  for (size_t i = 0; i < ARRAY_SIZE(recv_items); i++) {
    if (receive->protocol[TBYTE] & (1 << recv_items[i].table)) {
      receive->meta.entry_delim = recv_items[i].delim;
      return recv_items[i].func(receive);
    }
  }
  Message_Info("failure, init table");
  return FAIL;
}

int8_t receive_driver(recv_t *receive) {
  if (receive->protocol[ABYTE] & (1 << RWBIT)) {
    Message_Info(receive->recv);
  } else {
    return init_table(receive);
  }
  return SUCC;
}
