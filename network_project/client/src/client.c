#include "scan.h"
#include "client.h"

void client_input(cent_t *client, char *message) {

  scan_t scan = scan_driver(message);

  client->length = scan.length;
  strncpy(client->request, scan.scanner, scan.length);
}

/*
void print_byte(uint8_t byte) {
  for (uint8_t i = 1 << 7; i > 0; i = i / 2)
    (byte & i) ? printf("1") : printf("0");
}
*/
