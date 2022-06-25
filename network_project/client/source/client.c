/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    CLIENT
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#include "cstring.h"
#include "scanner.h"
#include "client.h"

void publisher(recv_t *receive) {
  for (int32_t i = 0; i < receive->count_rows; i++) {
    printf(
      "set:\t\t%c\nuser:\t\t%s\ndatetime:\t\t%s\ntopic\t\t%s\nmessage:\t\t%s\n\n",
      receive->table_mesg[i].set, receive->table_mesg[i].user,
      receive->table_mesg[i].datm, receive->table_mesg[i].topc,
      receive->table_mesg[i].mesg
    );
  }
}

int8_t client_driver(client_t *client) {

  int8_t result = 0;

  rqst_t request = {.status = 1};
  recv_t receive = {.status = 1};

  result = command_driver(request.protocol, receive.protocol);
  if (!result) return result;

  result = check_prcl(&request);
  if (!result) return result;

  request.size_user = string_copy(request.user, client->conn->user, SBUFF);

  result = request_driver(&request);
  if (!result) return result;

  request.size_send = send(client->conn->socket_client, request.rqst, request.size_rqst, 0);
  result = check_send(&request);
  if (!result) return result;
  
  receive.size_recv = recv(client->conn->socket_client, receive.recv, FBUFF, 0);
  result = check_recv(&receive);
  if (!result) return result;  

  result = receive_driver(&receive);
  if (!result) return result;
  
  publisher(&receive);
  free(receive.table_mesg);

  return SUCC;
}