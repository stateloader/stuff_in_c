#include "scan.h"
#include "command.h"
#include "client.h"


void client_session(cent_t *client) {

  while (client->state &= (1 << CMND))
    command_driver(client->command, &client->state);
}
