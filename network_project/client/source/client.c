/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    CLIENT
--------------------------------------------------------------------------------------------------------------------------
Info info info.
------------------------------------------------------------------------------------------------------------------------*/

#include "cstring.h"
#include "scanner.h"
#include "client.h"

static uint8_t send_request_package(int32_t socket_client, rqst_t *request) {
//desc

  request->size_send = send(socket_client, request->pack, request->size_pack, 0);
  return SUCC;
}

static uint8_t read_receive_package(int32_t socket_client, recv_t *receive) {
//desc

  receive->size_recv = recv(socket_client, receive->recv, FBUFF, 0);
  if (receive->protocol[EINDX] & (1 << RWBIT))
    return receive_driver(receive);
  else
    System_Message(receive->recv);
  return SUCC;
}

int8_t client_driver(client_t *client) {
//desc

  int8_t result = 0;
  rqst_t request = {0};
  recv_t receive = {0};

  result = command_driver(request.protocol, receive.protocol);
  if (result < 0) return result;

  request.size_user = string_copy(request.user, client->conn->user, SBUFF);

  result = request_driver(&request);
  if (!result) return result;

  result = send_request_package(client->conn->socket_client, &request);
  if (!result) return result;

  result = read_receive_package(client->conn->socket_client, &receive);
  if (!result) return result;

  if (receive.table_mesg) free(receive.table_mesg);
  return SUCC;
}