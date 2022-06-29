/*------------------------------------------------------------------------------------------------------------------------
                                                                                                             READER
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include "sstring.h"
#include "reader.h"

static int8_t phase_file_open(server_t *server, const char *path) {

  server->dbfile = fopen(path, "r");
  if (!server->dbfile) {
    Message_Info("attans ej readable");
    return FAIL;
  }
  return SUCC;
}

static int8_t phase_file_read(server_t *server) {

  server->size_resp = fread(server->resp, sizeof(char), FBUFF, server->dbfile);
  fclose(server->dbfile);
  return SUCC;
}

//------------------------------------------------------------------------------------------------------------------------

static int8_t read_mesg(server_t *server) {

  phase_file_open(server, "drivers/database/mesglog.dat");
  phase_file_read(server);
  return SUCC;
}

static int8_t read_dvce(server_t *server) {
  Message_Info("inside read dvce");

  phase_file_open(server, "drivers/database/dvcelog.dat");
  phase_file_read(server);
  return SUCC;
}

static read_item read_items[] = {
  {TMESG, read_mesg}, {TDVCE, read_dvce}
};

int8_t database_reader(server_t *server) {
 
  for (size_t i = 0; i < ARRAY_SIZE(read_items); i++) {
    if (server->protocol[TINDX] & (1 << read_items[i].table))
      return read_items[i].func(server);
  }
  Message_Info("Oh crap (read_driver)");
  return FAIL;
}