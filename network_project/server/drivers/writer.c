/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    WRITER
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include "socket.h"
#include "sstring.h"
#include "writer.h"

static int8_t phase_file_open(server_t *server, const char *path) {

  server->dbfile = fopen(path, "a");
  return check_file_open(server);
}

static int8_t phase_file_appd(server_t *server) {

  server->size_pack -= POFFS;
  int32_t size_write = fwrite(server->pack, sizeof(char), server->size_pack, server->dbfile);
  fclose(server->dbfile);
  check_size_appd(server, size_write);

  return SUCC;
}

static int8_t response_writer(server_t *server, char *response) {

  server->size_resp = string_copy(server->resp, response, SBUFF);
  return SUCC;

}
static int8_t write_mesg(server_t *server) {

  phase_file_open(server, "drivers/database/mesg.dat");
  phase_file_appd(server);
  response_writer(server, "your message was successfully recieved.");
  
  return SUCC;
}

static int8_t write_dvce(server_t *server) {

  phase_file_open(server, "drivers/database/dvce.dat");
  phase_file_appd(server);
  response_writer(server, "device led now glows in <whatever>");
  
  Message_Info("contact atmega etc...");
  
  return SUCC;
}

static int8_t writer_valid(server_t *server) {

  phase_file_open(server, "drivers/database/user.dat");
  phase_file_appd(server);
  response_writer(server, "your account has been created.");
  
  return SUCC;
}

static write_item table_items[] = {
  {TMESG, write_mesg}, {TDVCE, write_dvce}
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
  if (server->protocol[SBYTE] & (1 << VALID))
    return writer_items(server, table_items, ARRAY_SIZE(table_items), TBYTE);
  else
    return writer_valid(server);
}
 