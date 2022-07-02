/*-----------------------------------------------------------------------------------------------------------------RECEIVE
Logic dealing with creation of device requests; send (interact with device) or read historical records from the server.
Logic dealing with creation of message-requests; send to or read historical records from the server.
------------------------------------------------------------------------------------------------------------------------*/
#include "models.h"
#include "receive.h"

static int8_t table_mesg(recv_t *receive) {
/*First I made a generic, recursive solution of some sort but it turned out to be (way) to messy. Instead, every table,
 *current or later added, going to be hardcoded after the principle below.
 */
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
      receive->table_mesg[row].id = row;
      mem = 0, idx = 0, row++;
    }
    break;
    default:
      System_Message("oh noes");
    return EXIT;
    }
  }
  return SUCC;
}

static int8_t table_dvce(recv_t *receive) {

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
      receive->table_dvce[row].id = row;
      mem = 0, idx = 0, row++;
    }
    break;
    default:
      System_Message("oh noes");
    return EXIT;
    }
  }
  return SUCC;
}

static int8_t fetch_rows(recv_t *receive) {

  receive->size_recv -= POFFS;

  printf("amnt_delm %d\n", receive->amnt_delm);
  printf("amnt_rows %d\n", receive->amnt_rows);
  printf("tabl_delm %d\n", receive->tabl_delm);

  for (int32_t i = 0; i < receive->size_recv; i++)
    receive->amnt_delm += (receive->recv[i] == DELIM) ? 1 : 0;
  receive->amnt_rows = (receive->amnt_delm / receive->tabl_delm);

  printf("amnt_delm %d\n", receive->amnt_delm);
  printf("amnt_rows %d\n", receive->amnt_rows);
  printf("tabl_delm %d\n", receive->tabl_delm);

 // if (receive->amnt_rows % receive->amnt_delm != 0) {
   // System_Message("delimiter-count corrupted.");
    //return FAIL;
  //}
  return SUCC;
}

static int8_t fetch_memo(recv_t *receive) {

  int8_t result = 0;

  if (receive->protocol[TBYTE] & (1 << TMESG)) {
    receive->table_mesg = malloc(sizeof(mmod_t) * receive->amnt_rows);
    result = (receive->table_mesg != NULL) ? SUCC : FAIL;

  } else if (receive->protocol[TBYTE] & (1 << TDVCE)) {
    receive->table_dvce = malloc(sizeof(dmod_t) * receive->amnt_rows);
    result = (receive->table_dvce != NULL) ? SUCC : FAIL;

  } else {
    System_Message("there's no table-bit set");
    return FAIL;

  } if (result != SUCC) {
    System_Message("memory error while locating table instances");
    return FAIL;
  }
  return SUCC;
}

static int8_t fetch_table(recv_t *receive) {
  
  if (receive->protocol[TBYTE] & (1 << TMESG))
    return table_mesg(receive);

  if (receive->protocol[TBYTE] & (1 << TDVCE))
    return table_dvce(receive);
  return FAIL;
}

typedef int8_t (*fetch_func)(recv_t *receive);

typedef struct FetchItem {
  fetch_func func;
} fetch_item;

static fetch_item items[] = {
  {fetch_rows}, {fetch_memo}, {fetch_table}
};

static int8_t fetch_init(recv_t *receive) {

  if (receive->protocol[TBYTE] & (1 << TMESG))
    receive->tabl_delm = DMSGE;
  if (receive->protocol[TBYTE] & (1 << TDVCE))
    receive->tabl_delm = DDVCE;

  for (size_t i = 0; i < ARRAY_SIZE(items); i++) {
    if (items[i].func(receive) != SUCC)
      return FAIL;
  }
  receive->protocol[SBYTE] |= (1 << LINKA);
  return SUCC;
}

static int8_t protocol_parser(recv_t *receive) {

  if (receive->protocol[SBYTE] & (0 << VALID)) {
    System_Message(receive->recv);                                                            // felmeddelande;
    return FAIL;
  } else if (receive->protocol[ABYTE] & (1 << RWBIT)) {
    System_Message(receive->recv);                                                            //  validerar datainjektion
    return SUCC;
  } else {
    return fetch_init(receive);
  }
}

static int8_t protocol_obtain(recv_t *receive) {
/*Assigns the protocol from the package before some obtain-checks (inlines in header)*/

  receive->protocol[TBYTE] = receive->recv[receive->size_recv - 4];
  receive->protocol[ABYTE] = receive->recv[receive->size_recv - 3];
  receive->protocol[SBYTE] = receive->recv[receive->size_recv - 2];

  return protocol_obtain_checks(receive);
}

int8_t receive_driver(recv_t *receive) {

  int8_t result = 0;

  result = protocol_obtain(receive);
  if (result != SUCC) return result;

  result = protocol_parser(receive);
  if (result != SUCC) {
    release_memory(receive);
    return result;
  }
  return SUCC;
}

/*---------------------------------------------------------------------------------------------------------------TABLE BYTE
BIT(N)                              |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
CONSTANT                            |  UNBIT  |    -    |    -    |    -    |    -    |     -    |   TDVCE   |   TMESG   |
------------------------------------------------------------------------------------------------------------ATTRIBUTE BYTE
BIT(N)                              |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
CONSTANT                            |  UNBIT  |  RWBIT  |  ATTR5  |  ATTR4  |  ATTR3  |   ATTR2  |   ATTR1   |   ATTR0   |
-------------------------------------------------------------------------------------------------------------- STATUS BYTE
                                    |  UNBIT  |  VALID  |  SETUP  |  LOGIN  |    -    |     -    |     -     |     -     |
------------------------------------------------------------------------------------------------------------------------*/