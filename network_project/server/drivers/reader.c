/*------------------------------------------------------------------------------------------------------------------READER
                                                                                                            
------------------------------------------------------------------------------------------------------------------------*/
#include "sstring.h"
#include "reader.h"

static int8_t reader_file_open(server_t *server, const char *path) {

  server->dbfile = fopen(path, "r");
  return reader_file_open_check(server);
}

static int8_t reader_file_read(server_t *server) {

  server->size_resp = fread(server->resp, sizeof(char), FBUFF, server->dbfile);
  if (server->dbfile) fclose(server->dbfile);

  return reader_file_data_check(server);
}

static int8_t reader_file_mesg(server_t *server) {
  System_Message("reading from database mesg");

  server->session |= (1 << SMESG);
  int8_t result = 0;

  result = reader_file_open(server, "drivers/database/mesg.dat");
  if (result != SUCC) return result;
  
  result = reader_file_read(server);
  if (result != SUCC) return result;

  return SUCC;
}

static int8_t reader_file_dvce(server_t *server) {
  System_Message("reading from database dvce");

  server->session |= (1 << SDVCE);
  int8_t result = 0;

  result = reader_file_open(server, "drivers/database/dvce.dat");
  if (result != SUCC) return result;

  result = reader_file_read(server);
  if (result != SUCC) return result;

  return SUCC;
}

static read_item table_items[] = {
  {TMESG, reader_file_mesg}, {TDVCE, reader_file_dvce}
};

static int8_t reader_items(server_t * server, read_item *items, size_t size_arr, uint8_t byte) {
  
  for (size_t i = 0; i < size_arr; i++) {
    if (server->protocol[byte] & (1 << items[i].flag))
      return items[i].func(server);
  }
  server->session |= (1 << RPROB);
  System_Message("\nServer Error\n- flag for reader items\n");
  return FAIL;
}

int8_t database_reader(server_t *server) {
  return reader_items(server, table_items, ARRAY_SIZE(table_items), TBYTE);
}
/*
static int8_t reader_valid(server_t *server) {
  Message_Info("inside reader_valid");

  int8_t result = 0;

  result = reader_file_open(server, "drivers/database/user.dat");
  if (result != SUCC) return result;

  result = reader_file_read(server);
  if (result != SUCC) return result;

  return SUCC;
}
*/