#include "cstring.h"
#include "scanner.h"

#include "client.h"

static void enter_username(client_t *client) {
  Render_Header("USERNAME", "Tell who you are!");
  client->meta->size_user = scan_driver(client->meta->username, SBUFF, "username");
}

int8_t client_driver(client_t *client) {

  enter_username(client);

  cmnd_t command = {.status = 1};
  rqst_t request = {.status = 1};

  if (!command_driver(&command))
    return QUIT;

  request.rqst_byte = command.rqst_byte;

  if ((request.size_user = string_copy(request.user, client->meta->username, SBUFF)) < 1)
    return KILL;
  
  request_driver(&request);
  
  return SUCC;
}