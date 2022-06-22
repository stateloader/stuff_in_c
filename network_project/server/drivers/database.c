/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                  DATABASE
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include "reader.h"
#include "writer.h"
#include "database.h"

static write_item write_items[] = {
  {0x03, "dbfiles/messages.dat"},
  {0x02, "dbfiles/device.dat"}
};

static read_item read_items[] = {
  {0x03, "dbfiles/messages.dat"},
  {0x02, "dbfiles/device.dat"}
};

int8_t database_driver(data_t *database) {
  System_Message("Inside database driver");
  return SUCC;
}