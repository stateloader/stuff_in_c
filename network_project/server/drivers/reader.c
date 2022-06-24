/*------------------------------------------------------------------------------------------------------------------------
                                                                                                             READER
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include "sstring.h"
#include "reader.h"

static void phase_file_open(server_t *server, const char *path) {
  System_Message("inside phase file_open");

  server->dbfile = fopen(path, "r");
  if (!server->dbfile) {
    System_Message("attans ej readable");
  }
}

static void phase_file_read(server_t *server) {
  System_Message("inside phase file_read");

  server->size_resp = fread(server->resp, sizeof(char), FBUFF, server->dbfile);
  fclose(server->dbfile);
}

//------------------------------------------------------------------------------------------------------------------------

static void read_mesg(server_t *server) {
  System_Message("inside dread mesg");

  phase_file_open(server, "drivers/database/message.dat");
  phase_file_read(server);
}

static void read_dvce(server_t *server) {
  System_Message("inside read dvce");

  phase_file_open(server, "drivers/database/device.dat");
  phase_file_read(server);
}

static read_item read_items[] = {
  {TMESG, read_mesg}, {TDVCE, read_dvce}
};

void read_driver(server_t *server) {
  System_Message("Inside read_driver");
 
  for (size_t i = 0; i < ARRAY_SIZE(read_items); i++) {
    if (server->protocol[TINDX] & (1 << read_items[i].table))
      return read_items[i].func(server);
  }
  System_Message("Oh crap (read_driver)");
  return;
}