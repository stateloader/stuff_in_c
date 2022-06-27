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

  int8_t result = 0;
  rqst_t request = {0}; recv_t receive = {0};
  request.size_user = string_copy(request.user, client->conn->user, SBUFF);

  rout_t routine = ROUT_CMND;

  while (routine != ROUT_DONE) {
    switch(routine) {
    case ROUT_CMND:
      result = command_driver(request.protocol, receive.protocol);
      if (result <= FAIL)
        routine = ROUT_DONE;
      else
        routine = ROUT_RQST;
      break;
    case ROUT_RQST:
      result = request_driver(&request);
      if (result != SUCC)
        routine = ROUT_DONE;
      else
        routine = ROUT_SEND;
      break;
    case ROUT_SEND:
      result = client_package(client->conn->socket_client, &request);
      if (result != SUCC)
        routine = ROUT_DONE;
      else
        routine = ROUT_RECV;
      break;
    case ROUT_RECV:
      result = server_package(client->conn->socket_client, &receive);
      if (result != SUCC)
        routine = ROUT_DONE;
      else
        routine = ROUT_FWRD;
      break;
    case ROUT_FWRD:
      result = receive_driver(&receive);
      if (result != SUCC)
        routine = ROUT_DONE;
      else
        routine = ROUT_DONE;
      break;
    default:
      System_Message("client routine fail");
      exit(EXIT_FAILURE);
    }
  }
  return result;
}