/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                  DATABASE
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include "reader.h"
#include "writer.h"
#include "database.h"

static write_item write_items[] = {
  {0x00, "drivers/saker/users.dat"},
  {0x01, "drivers/saker/samples.dat"},
  {0x02, "drivers/saker/device.dat"},
  {0x03, "drivers/saker/messages.dat"}
};

static int8_t database_action(data_t *database) {
  System_Message("Inside database action.\n");
  System_Message(database->recv);

  return SUCC;
}

static int8_t database_writer(data_t *database) {
  System_Message("Inside database writer.\n");
  System_Message(database->recv);

  write_t writer = {.status = 1};
  writer.item = &write_items[database->model];

  writer.size_appd = string_copy(writer.appd, database->recv, SBUFF);

  return write_driver(&writer);
}

static int8_t database_reader(data_t *database) {
  System_Message("Inside database reader.\n");
  System_Message(database->recv);

  read_t reader = {.status = 1};

  return SUCC;
}

static int8_t database_routes(data_t *database) {
  System_Message("Inside database routes.\n");

  database->model = decode_model(database->reqbyte);
  database->trigg = decode_trigg(database->reqbyte);
  database->rwbit = decode_rwbit(database->reqbyte);

  return database->model;
}

int8_t database_driver(data_t *database) {
  System_Message("Inside database driver.\n");

  if (database_routes(database) < 0)
    return FAIL;

  if (database->rwbit)
    return database_writer(database);
  else
    return database_reader(database);
}