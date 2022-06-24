/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    CLIENT
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#include "cstring.h"
#include "scanner.h"
#include "client.h"

static void request_commit(conn_t *conn, rqst_t *request) {
  int32_t result = send(conn->socket_client, request->rqst, request->size_rqst, 0);
  Print_Numb(result, "skickad");
  return;
}

void client_driver(client_t *client) {

  rqst_t request = {.status = 1};
  request.size_user = string_copy(request.user, client->conn->user, SBUFF);

  command_driver(request.protocol);
  request_driver(&request);
  request_commit(client->conn, &request);
}