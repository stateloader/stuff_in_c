#include "cstring.h"
#include "scanner.h"

#include "client.h"

static char *impossible_secret = "pass";

static void enter_username(client_t *client) {
  System_Message("Iside enter_username");
  client->meta->size_user = scan_driver(client->meta->username, SBUFF, "username");
}

int8_t client_driver(client_t *client) {
  System_Message("Inside client_driver");

  meta_t meta = {.status = 1};
  cmnd_t cmnd = {.status = 1};
  rqst_t rqst = {.status = 1};

  client->meta = &meta;
  client->command = &cmnd;
  client->request = &rqst;
  
  command_driver(client->command);

  return SUCC;
}