/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                  DATABASE
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------Request Endbyte
Bit                                 |    7    |    6    |    5    |    4    |    3    |     2    |     1     |     0     |
Constant                            |  RWBIT  |  RACT2  |  RACT1  |  RACT0  |  RMSGE  |   RDVCE  |   RDATA   |   RCONN   |
                                    --------------------------------------------------------------------------------------
MCONN   Request Connection          Get flags server to init connection stuff (i.e user login/signup).
MDATA   Request Data                Get flags server to init data/fetch (from database) stuff.
MDVCE   Request Device              Get flags server to init interaction with device stuff.
MMSGE   Request Message             Get flags server to init message stuff.
RACTN   Request Action (N)          Bit 4 to 6 used for flagging stuff to the server.
RWBIT   Request Read/Write          Get flags server it's a writing (to database) errant, cleared reading from it.
------------------------------------------------------------------------------------------------------------------------*/

#include "sconfig.h"
#include "reader.h"
#include "writer.h"
#include "database.h"

static const char *FILEPATHS[] = {
  "drivers/saker/users.txt",
  "drivers/saker/samples.dat",
  "drivers/saker/device.dat",
  "drivers/saker/messages.txt"
};

static int8_t database_read(server_t *server) {
  System_Message("Inside database_read.");

  read_t reader = {.route = server->endbyte};
  return SUCC;
}

static int8_t database_write(server_t *server) {
  System_Message("Inside database_write.");

  int8_t model = 0, action = 0;

  if ((model = check_model(server->endbyte)) < 0) {
    System_Message("something went south parsing model");
    return FAIL;
  } else if ((action = check_action(server->endbyte)) < 0) {
    System_Message("something went south parsing action");
    return FAIL;
  }
  server->recv[server->size_recv - 2] = '\0';
  server->size_recv--;
  //removing endbyte by assign nullterminator before reducing size.

  wrim_t witem = {
    .model = model,
    .action = action,
    .size_package = server->size_recv,
    .package = server->recv,
    .filepath = FILEPATHS[model]
  };

  write_t writer = {.status = 0,.witem = witem};

  return write_driver(&writer);
}

int8_t database_driver(server_t *server) {
  System_Message("Inside database driver.\n");

  if (server->endbyte & (1 << RMSGE))
    return database_write(server);
  else  
    return database_read(server);
}