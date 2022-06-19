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

static read_item read_items[] = {
  {0x00, "drivers/saker/users.dat"},
  {0x01, "drivers/saker/samples.dat"},
  {0x02, "drivers/saker/device.dat"},
  {0x03, "drivers/saker/messages.dat"}
};

static int8_t database_action(data_t *database) {
//desc
  System_Message("Inside database action");
  System_Message(database->recv);

  int8_t action_result = 0;

  return action_result;
}

static int8_t database_writer(data_t *database) {
//desc
  System_Message("Inside database writer");
  System_Message(database->recv);

  write_t writer = {.status = 1};
  writer.item = &write_items[database->model];

  writer.size_appd = string_copy(writer.appd, database->recv, SBUFF);

  int8_t writer_result = write_driver(&writer);

  return writer_result;
}

static int8_t database_reader(data_t *database) {
//desc
  System_Message("Inside database reader");
/*
  read_t reader = {.status = 1};
  reader.item = &write_items[database->model];
  
  if(!read_driver(&reader)) return FAIL;

  database->size_resp = string_copy(database->resp, reader.file_data, FBUFF);

  return database_reader_check(database->size_resp, reader.size_file);
*/
  return SUCC;
}

static int8_t database_routes(data_t *database) {
  System_Message("Inside database routes");

  database->model = decode_model(database->reqbyte);
  database->trigg = decode_trigg(database->reqbyte);
  database->rwbit = decode_rwbit(database->reqbyte);

  return database->model;
}

int8_t database_driver(data_t *database) {
  System_Message("Inside database driver");

  if (database_routes(database) < 0)
    return FAIL;

  if (database->rwbit)
    return database_writer(database);
  else
    return database_reader(database);
}