/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    WRITER
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include "socket.h"
#include "sstring.h"
#include "writer.h"

static int8_t phase_file_open(server_t *server, const char *path) {
  Message_Info("inside phase file_open");

  server->dbfile = fopen(path, "a");
  return check_file_open(server);
}

static int8_t phase_file_appd(server_t *server) {
  Message_Info("inside phase file_append");

  server->size_pack -= POFFS;
  int32_t size_write = fwrite(server->pack, sizeof(char), server->size_pack, server->dbfile);
  fclose(server->dbfile);
  check_size_appd(server, size_write);

  return SUCC;
}

static int8_t response_writer(server_t *server, char *response) {
  Message_Info("inside phase file_append");
  server->size_resp = string_copy(server->resp, response, SBUFF);
  return SUCC;

}
//------------------------------------------------------------------------------------------------------------------------
static int8_t write_mesg(server_t *server) {
  Message_Info("inside write mesg");

  phase_file_open(server, "drivers/database/mesglog.dat");
  phase_file_appd(server);
  response_writer(server, "your message was successfully recieved.");
  
  return SUCC;
}

static int8_t write_dvce(server_t *server) {
  Message_Info("inside write dvce");

  phase_file_open(server, "drivers/database/dvcelog.dat");
  phase_file_appd(server);
  response_writer(server, "device led now glows in <whatever>");
  
  Message_Info("contact atmega etc...");
  
  return SUCC;
}

static write_item write_items[] = {
  {TMESG, write_mesg}, {TDVCE, write_dvce}
};

int8_t database_writer(server_t *server) {
  Message_Info("inside filewriter");
 
  for (size_t i = 0; i < ARRAY_SIZE(write_items); i++) {
    if (server->protocol[TINDX] & (1 << write_items[i].model))
      return write_items[i].func(server);
  }
  return FAIL;
}