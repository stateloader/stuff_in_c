/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    CLIENT
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#include "cstring.h"
#include "scanner.h"
#include "client.h"

void client_driver(client_t *client) {

  uint8_t protocol[3] = {'\0'};
  command_driver(protocol);

  rqst_t request = {.status = 1,.protocol = protocol};
  recv_t receive = {.status = 1,.protocol = protocol};

  request.size_user = string_copy(request.user, client->conn->user, SBUFF);
  request_driver(&request);

  request.size_send = send(client->conn->socket_client, request.rqst, request.size_rqst, 0);  
  receive.size_recv = recv(client->conn->socket_client, receive.recv, FBUFF, 0);

  receive_driver(&receive);
}