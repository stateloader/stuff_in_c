#include "client.h"

void client_request(cent_t *client, char *message) {

  scan_t scan = scan_driver(message);
  client->sizereq = scan.length;
  strncpy(client->request, scan.scanner, client->sizereq);
}
