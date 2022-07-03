/*------------------------------------------------------------------------------------------------------------------WRITER
                                                                                                            
------------------------------------------------------------------------------------------------------------------------*/
#include "socket.h"
#include "sstring.h"
#include "writer.h"

int8_t writer_protocol_respond(server_t *server) {

  server->size_resp = POFFS;

  server->resp[server->size_resp - 4] = server->protocol[TBYTE];
  server->resp[server->size_resp - 3] = server->protocol[ABYTE];
  server->resp[server->size_resp - 2] = server->protocol[SBYTE];
  server->resp[server->size_resp - 1] = '\0';

  return SUCC;
}

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
  System_Message("writing to database mesg");

  server->session |= (1 << SMESG);
  int8_t result = 0;

  result = writer_file_open(server, "drivers/database/mesg.dat");
  if (result != SUCC) return result;
  
  result = writer_file_appd(server);
  if (result != SUCC) return result;
  
  return SUCC;
}

static int8_t writer_dvce(server_t *server) {
  System_Message("writing to database dvice");

  server->session |= (1 << SDVCE);
  int8_t result = 0;

  result = writer_file_open(server, "drivers/database/dvce.dat");
  if (result != SUCC) return result;
  
  result = writer_file_appd(server);
  if (result != SUCC) return result;
  
  System_Message("contact atmega etc...");
  
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
  server->session |= (1 << WPROB);
  System_Message("\nbyte-troubles in reader_items\n");
  return FAIL;
}

int8_t database_writer(server_t *server) {
  System_Message("inside filewriter");
  return writer_items(server, table_items, ARRAY_SIZE(table_items), TBYTE);
}