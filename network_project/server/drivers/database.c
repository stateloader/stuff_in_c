/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                  DATABASE
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include "reader.h"
#include "writer.h"
#include "database.h"
/*
  umod_t *table_user;
  smod_t *table_samp;
  dmod_t *table_dvce;
  mmod_t *table_mesg;
*/
int8_t database_read(server_t *server) {
  System_Message("Inside database_read.\n");

  read_t reader = {.status = 0x00};
  server->table = (mmod_t*)reader.table_mesg;
  return SUCC;
}

int8_t database_write(server_t *server) {
  System_Message("Inside database_write.\n");

  write_t writer = {.status = 0x00};
  return SUCC;
}

int8_t database_driver(server_t *server) {
  System_Message("Inside database driver.\n");

  int8_t result = 0;

  switch(server->dborder) {
  case INITR:
    result = database_read(server);
    break;
  case INITW:
    result = database_write(server);
    break;
  default:
    System_Message("Something went south database_driver");
    result = FAIL;
  } 
  return result;
}