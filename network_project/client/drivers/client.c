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
  publisher(&receive);
  free(receive.table_mesg);
}