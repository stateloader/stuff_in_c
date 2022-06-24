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
 
 // int8_t task = server->protocol[TINDX];
  for (size_t i = 0; i < ARRAY_SIZE(write_items); i++) {
    if (server->protocol[TINDX] & (1 << write_items[i].model))
      write_items[i].func(server);
    else
      System_Message("TDVICE-fix");
  }
}