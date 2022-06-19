#include "cstring.h"
#include "scanner.h"

#include "client.h"

static char *impossible_secret = "pass";

static void enter_username(client_t *client) {
  Render_Header("USERNAME", "Tell who you are!");
  client->meta->size_user = scan_driver(client->meta->username, SBUFF, "username");
}

int8_t client_driver(client_t *client) {

  enter_username(client);

  cmnd_t cmnd = {.status = 1};
  rqst_t rqst = {.status = 1};

  if (command_driver(&cmnd) < 0)
    return QUIT;

  rqst.rqst_byte = cmnd.rqst_byte;
  request_driver(&rqst);
  
  return SUCC;
}