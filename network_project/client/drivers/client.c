#include "cstring.h"
#include "scanner.h"

#include "client.h"

static void fetch_protocol(uint8_t *dest, uint8_t *from) {
  for (int8_t i = 0; i < 3; i++)
    dest[i] = from[i];
} 

static void fetch_username(client_t *client) {
  Render_Header("USERNAME", "Tell who you are!");
  client->meta->size_user = scan_driver(client->meta->user, SBUFF, "username");
}

int8_t client_driver(client_t *client) {

  uint8_t protocol[3] = {'\0'};
  rqst_t request = {.status = 1};

  fetch_username(client);

  if (!command_driver(protocol)) return FAIL;

  fetch_protocol(request.protocol, protocol);

  request.size_user = string_copy(request.user, client->meta->user, SBUFF);
  request_driver(&request);

  return SUCC;
}