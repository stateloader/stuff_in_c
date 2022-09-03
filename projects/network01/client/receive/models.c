/*--------------------------------------------------------------------------------------------MODELS
When the client/user has sent a read-requests, a corresponding database (entire, for now) will be
sent back from the server. The model-structs below are used for creating rows/instances out of this
data - "tables".
--------------------------------------------------------------------------------------------------*/
#include "stdlib.h"
#include "models.h"

mmod_t *table_mesg_create(const char *package, size_t size_pack, size_t size_rows) {
/*Instances being malloced times amount of rows where every member of every instance being assigned
 *by sniffing delimiters.*/

  mmod_t *table_mesg = malloc(sizeof(mmod_t) * size_rows);
  if (table_mesg == NULL)
		Termination_Message("table_mesg_create", "memory allocation failure.");

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
      if (table_mesg) free(table_mesg);
    	Termination_Message("table_mesg_create", "default reached in switch-statement.");
    }
  }
  return table_mesg;
}
dmod_t *table_dvce_create(const char *package, size_t size_pack, size_t size_rows) {
/*Same principle as above but for device-data.*/

  dmod_t *table_dvce = malloc(sizeof(dmod_t) * size_rows);
  if (table_dvce == NULL)
    Termination_Message("table_dvce_create", "memory allocation failure.");

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
    	if (table_dvce) free(table_dvce);
    	Termination_Message("table_dvce_create", "default reached in switch-statement.");
    }
  }
  return table_dvce;
}
