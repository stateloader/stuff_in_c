/*-------------------------------------------------------------------------------------------------------------------MODELS
When the client/user has sent a read-requests (from a given database) its (entire, for now) content going to be sent from
the server. The model-structs are used for creating rows/instances, these in turn collected into 'tables'. This is done
by titerate through the received raw database-string as shown in this source file.

At first, I'd a more generic solution in place involving recursion and some fanzy stuff but it turned out even messier than
this hard-coded solution.
-------------------------------------------------------------------------------------------------------------------------*/
#include "stdlib.h"
#include "models.h"

mmod_t *table_mesg_create(const char *package, size_t size_pack, size_t rows, uint8_t *state, uint16_t *error) {
/*After the raw package (given database; messsage, device and <future stuff>), its size and amount of rows/instances it
 *contains will be fed into this (a) table_create function.
 
 *Here, instances being malloced times amount of rows where every member of every instance being assigned by sniffing
 *delimiters.*/

  mmod_t *table_mesg = malloc(sizeof(mmod_t) * rows);
  if (table_mesg == NULL) {
    *state |= (1 << ERROR); *error |= (1 << MMERR);
    return NULL;
  }

  size_t mem = 0, idx = 0, row = 0;
  
  for (size_t i = 0; i < size_pack; i++) {

    switch(mem) {
    case 0:
    if (package[i] != DELIM) {
      table_mesg[row].user[idx] = package[i];
      idx++;
    } else {
      table_mesg[row].user[idx] = '\0';
      mem++, idx = 0;
    }
    break;
    case 1:
    if (package[i] != DELIM) {
      table_mesg[row].datm[idx] = package[i];
      idx++;
    } else {
      table_mesg[row].datm[idx] = '\0';
      mem++, idx = 0;
    }
    break;
    case 2:
    if (package[i] != DELIM) {
      table_mesg[row].topc[idx] = package[i];
      idx++;
    } else {
      table_mesg[row].topc[idx] = '\0';
      mem++, idx = 0;
    }
    break;
    case 3:
    if (package[i] != DELIM) {
      table_mesg[row].mesg[idx] = package[i];
      idx++;
    } else {
      table_mesg[row].mesg[idx] = '\0';
      table_mesg[row].id = row;
      mem = 0, idx = 0, row++;
    }
    break;
    default:
    *state |= (1 << ERROR); *error |= (1 << SDERR);
    if (table_mesg) free(table_mesg);
    }
  }
  return table_mesg;
}
dmod_t *table_dvce_create(const char *package, size_t size_pack, size_t rows, uint8_t *state, uint16_t *error) {

  dmod_t *table_dvce = malloc(sizeof(dmod_t) * rows);
  if (table_dvce == NULL) {
    *state |= (1 << ERROR); *error |= (1 << MMERR);
    return NULL;
  }

  size_t mem = 0, idx = 0, row = 0;
  for (size_t i = 0; i < size_pack; i++) {

    switch(mem) {
    case 0:
    if (package[i] != DELIM) {
      table_dvce[row].user[idx] = package[i];
      idx++;
    } else {
      table_dvce[row].user[idx] = '\0';
      mem++, idx = 0;
    }
    break;
    case 1:
    if (package[i] != DELIM) {
      table_dvce[row].datm[idx] = package[i];
      idx++;
    } else {
      table_dvce[row].datm[idx] = '\0';
      mem++, idx = 0;
    }
    break;
    case 2:
    if (package[i] != DELIM) {
      table_dvce[row].push[idx] = package[i];
      idx++;
    } else {
      table_dvce[row].push[idx] = '\0';
      table_dvce[row].id = row;
      mem = 0, idx = 0, row++;
    }
    break;
    default:
    *state |= (1 << ERROR); *error |= (1 << SDERR);
    if (table_dvce) free(table_dvce);
    }
  }
  return table_dvce;
}
