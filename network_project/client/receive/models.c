#include "stdlib.h"
#include "models.h"

mmod_t *table_mesg_create(const char *package, size_t size_pack, size_t rows,
                          uint8_t *state, uint16_t *error)
  {
  
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
    }
  }
  return table_mesg;
}
dmod_t *table_dvce_create(const char *package, size_t size_pack, size_t rows,
                          uint8_t *state, uint16_t *error)
  {

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
    }
  }
  return table_dvce;
}
