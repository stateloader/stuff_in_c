/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    WRITER
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include "socket.h"
#include "sstring.h"
#include "writer.h"


static int8_t writer_file_open(server_t *server, const char *path) {

  server->dbfile = fopen(path, "a");
  return check_file_open(server);
}

static int8_t writer_file_appd(server_t *server) {

  server->size_pack -= POFFS;

  int32_t size_write = fwrite(server->pack, sizeof(char), server->size_pack, server->dbfile);
  fclose(server->dbfile);

  return check_size_appd(server, size_write);
}

static int8_t writer_mesg(server_t *server) {

  int8_t result = 0;

  result = writer_file_open(server, "drivers/database/mesg.dat");
  if (result != SUCC) return result;
  
  result = writer_file_appd(server);
  if (result != SUCC) return result;
  
  return SUCC;
}

static int8_t writer_dvce(server_t *server) {

  int8_t result = 0;

  result = writer_file_open(server, "drivers/database/dvce.dat");
  if (result != SUCC) return result;
  
  result = writer_file_appd(server);
  if (result != SUCC) return result;
  
  Message_Info("contact atmega etc...");
  
  return SUCC;
}

static int8_t writer_valid(server_t *server) {

  Message_Info("inne i writervalid");
  int8_t result = 0;

  result = writer_file_open(server, "drivers/database/user.dat");
  if (result != SUCC) return result;
  
  result = writer_file_appd(server);
  if (result != SUCC) return result;

  return SUCC;
}

static write_item table_items[] = {
  {TMESG, writer_mesg}, {TDVCE, writer_dvce}
};

static int8_t writer_items(server_t * server, write_item *items, size_t size_arr, uint8_t byte) {
  
  for (size_t i = 0; i < size_arr; i++) {
    if (server->protocol[byte] & (1 << items[i].flag))
      return items[i].func(server);
  }
  Message_Info("byte-troubles in reader_items");
  return FAIL;
}

int8_t database_writer(server_t *server) {
  Message_Info("inside filewriter");

  if (server->protocol[SBYTE] & (1 << SETUP))
    return writer_valid(server);
  else
    return writer_items(server, table_items, ARRAY_SIZE(table_items), TBYTE);
}