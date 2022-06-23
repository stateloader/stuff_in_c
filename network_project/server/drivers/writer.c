/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    WRITER
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/
#include "writer.h"

static void phase_file_open(server_t *server, const char *path) {
  System_Message("inside phase file_open");
  server->dbfile = fopen(path, "a");

  if (!server->dbfile) {
    System_Message("couldn't open database. Let's panic a bit.")
    server->status = STATL;
  } else {
    System_Message("file opened.");
    return;
  }
}

static void phase_file_append(server_t *server) {
  System_Message("inside phase file_append");
}

static void write_mesg(server_t *server) {
  System_Message("inside write mesg");

}

static void write_dvce(server_t *server) {
  System_Message("inside write dvce");

}

static write_item write_items[] = {
  {TMESG, write_mesg},
  {TDVCE, write_dvce}
};

void write_driver(server_t *server) {
  System_Message("inside filewriter");

}