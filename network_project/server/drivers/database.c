/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                  DATABASE
--------------------------------------------------------------------------------------------------------------------------
info fasda
------------------------------------------------------------------------------------------------------------------------*/

#include "database.h"

static char *FILEPATHS[] = {
  "drivers/saker/users.dat", "drivers/saker/samples.dat",
  "drivers/saker/device.dat", "drivers/saker/messages.dat"
};

static int8_t database_read(server_t *server) {
  System_Message("Inside database_read.");
  
  server->reader.model = decode_model_check(server->endbyte);
  if (server->reader.model < 0)
    return FAIL;
  
  System_Message(server->recv);
  return SUCC;
}

static int8_t database_write(server_t *server) {
  System_Message("Inside database_write.");

  server->writer.model = decode_model_check(server->endbyte);
  server->writer.action = decode_action_check(server->endbyte);
  if (server->writer.model < 0 || server->writer.action < 0)
    return FAIL;

  server->size_recv -= 1;
  server->recv[server->size_recv - 1] = '\0';

  server->writer.size_appd = string_copy(server->writer.appd, server->recv, SBUFF);
  server->writer.size_path = string_copy(server->writer.path, FILEPATHS[server->writer.model], SBUFF);

  if (database_writer_check(server) < 0)
    return FAIL;
  else
    return write_driver(&server->writer);
}

int8_t database_driver(server_t *server) {
  System_Message("Inside database driver.\n");

  if (server->endbyte & (1 << RMSGE))
    return database_write(server);
  else  
    return database_read(server);
}