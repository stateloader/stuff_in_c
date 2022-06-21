/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    CLIENT
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#include "cstring.h"
#include "scanner.h"
#include "client.h"

void client_driver(client_t *client) {

  rqst_t request = {.status = 1};

  request.size_user = string_copy(request.user, client->meta->user, SBUFF);
  command_driver(request.protocol);
  request_driver(&request);
  System_Message(request.rqst);
}