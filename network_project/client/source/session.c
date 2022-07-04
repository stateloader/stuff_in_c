/*----------------------------------------------------------------------------------------------------------CLIENT SESSION

------------------------------------------------------------------------------------------------------------------------*/
#include "connect.h"
#include "session.h"

static int8_t session_config(rqst_t *request, recv_t *receive, client_t *client) {

  int8_t result = command_driver(client);
  if (result <= FAIL) return EXIT;

  request->protocol = client->protocol;
  request->socket = client->conn.socket_client;
  request->size_user = client->size_user;
  
  request->user = client->user;

  receive->protocol = client->protocol;
  receive->socket = client->conn.socket_client;  
  receive->size_user = client->size_user;

  receive->user = client->user;

  return routine_config_check(request, receive);
}

static int8_t client_package(rqst_t *request) {
  
  request->size_send = send(request->socket, request->pack, request->size_pack, 0);
  return SUCC;
}
               
static int8_t server_package(recv_t *receive) {
  
  receive->size_recv = recv(receive->socket, receive->recv, FBUFF, 0);
  return SUCC;
}

int8_t session_driver(client_t *client) {

  int8_t result = 0;
  rout_t routine = ROUT_CONF;
  rqst_t request = {0}; recv_t receive = {0};


  while (routine != ROUT_DONE) {

    switch(routine) {
    case ROUT_CONF:
      result = session_config(&request, &receive, client);
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
      result = client_package(&request);
      if (result != SUCC)
        routine = ROUT_DONE;
      else
        routine = ROUT_RESP;
      break;
    case ROUT_RESP:
      result = server_package(&receive);
      if (result != SUCC)
        routine = ROUT_DONE;
      else
        routine = ROUT_RECV;
      break;
    case ROUT_RECV:
      result = receive_driver(&receive);
      if (result != SUCC)
        routine = ROUT_DONE;
      else 
        routine = ROUT_FRWD;
      break;
    case ROUT_FRWD:
      routine = ROUT_DONE;
      break;
    default:
      System_Message("client routine fail");
      exit(EXIT_FAILURE);
    }
  }
  free_session_memory(&receive);
  return result;
}

     /* for (int32_t i = 0; i < receive.amnt_rows; i++) {
        printf("ID %d \t Username: %s \t Datetime: %s \t Topic: %s \t Message: %s\n",
          receive.table_mesg[i].id, receive.table_mesg[i].user,
          receive.table_mesg[i].datm, receive.table_mesg[i].topc,
          receive.table_mesg[i].mesg
        );
      }
      */