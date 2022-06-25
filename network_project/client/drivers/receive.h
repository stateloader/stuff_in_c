#ifndef RECEIVE_H_
#define RECEIVE_H_

#include "configs.h"
#include "models.h"

typedef struct Receive {
  int8_t status;
  uint8_t *protocol;
  char recv[FBUFF];
  int32_t size_recv;
  size_t this_delim;
  int32_t count_delm;
  int32_t count_rows;
  mmod_t *table_mesg;
  dmod_t *table_dvce;
} recv_t;

typedef void (*recv_func)(recv_t *receive);

typedef struct RecieveItem {
  const uint8_t table;
  const int32_t delim;
  recv_func func;
} recv_item;

void receive_driver(recv_t *receive);

inline static void distributor_mesg(recv_t *receive) {

  for (int32_t i = 0; i < receive->count_rows; i++)
    receive->table_mesg[i].id = i;

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

#endif