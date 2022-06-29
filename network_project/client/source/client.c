/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    CLIENT
--------------------------------------------------------------------------------------------------------------------------
Info info info.
------------------------------------------------------------------------------------------------------------------------*/

#include "cstring.h"
#include "scanner.h"
#include "client.h"

static uint8_t client_package(int32_t socket_client, rqst_t *request) {
  request->size_send = send(socket_client, request->pack, request->size_pack, 0);
  return SUCC;
}
               
static uint8_t server_package(int32_t socket_client, recv_t *receive) {
  receive->size_recv = recv(socket_client, receive->recv, FBUFF, 0);
  return SUCC;
}

int8_t client_driver(client_t *client) {

  rqst_t request = {0};
  recv_t receive = {0};
  rout_t routine = ROUT_CMND;

  request.size_user = string_copy(request.user, client->user, SBUFF);

  int8_t result = 0;
  //uint8_t protocol[3] = {0};

  while (routine != ROUT_DONE) {

    switch(routine) {
    case ROUT_CMND:
      result = command_driver(client->protocol);
      if (result <= FAIL)
        routine = ROUT_DONE;
      else
        routine = ROUT_RQST;
      break;
    case ROUT_RQST:
      request.protocol = client->protocol;
      result = request_driver(&request);
      if (result != SUCC)
        routine = ROUT_DONE;
      else
        routine = ROUT_SEND;
      break;
    case ROUT_SEND:
      result = client_package(client->socket_client, &request);
      if (result != SUCC)
        routine = ROUT_DONE;
      else
        routine = ROUT_RESP;
      break;
    case ROUT_RESP:
      result = server_package(client->socket_client, &receive);
      if (result != SUCC)
        routine = ROUT_DONE;
      else
        routine = ROUT_RECV;
      break;
    case ROUT_RECV:
      receive.protocol = client->protocol;
      result = receive_driver(&receive);
      if (result != SUCC)
        routine = ROUT_DONE;
      else
        routine = ROUT_FRWD;
      break;
    case ROUT_FRWD:
        // CRUD-stuff.
        routine = ROUT_DONE;
      break;
    default:
      Message_Info("client routine fail");
      exit(EXIT_FAILURE);
    }
  }
  return result;
}