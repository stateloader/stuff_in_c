/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    WRITER
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include "writer.h"

static void phase_file_open(server_t *server, const char *path) {
  System_Message("inside phase file_open");

  server->dbfile = fopen(path, "a");
  check_file_open(server);
}

static void phase_file_appd(server_t *server) {
  System_Message("inside phase file_append");

  server->size_recv -= POFFS;
  int32_t size_write = fwrite(
    server->recv, sizeof(char), server->size_recv, server->dbfile
  );
  check_size_appd(server, size_write);
  fclose(server->dbfile);
}
//------------------------------------------------------------------------------------------------------------------------
static void write_mesg(server_t *server) {
  System_Message("inside write mesg");

  phase_file_open(server, "drivers/database/message.dat");
  phase_file_appd(server);
}

static void write_dvce(server_t *server) {
  System_Message("inside write dvce");
}

static write_item write_items[] = {
  {TMESG, write_mesg}, {TDVCE, write_dvce}
};

void write_driver(server_t *server) {
  System_Message("inside filewriter");
  int8_t task = server->protocol[TINDX];
  
  write_items[0].func(server);
}