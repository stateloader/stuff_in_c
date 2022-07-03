/*----------------------------------------------------------------------------------------------------------CLIENT SESSION

------------------------------------------------------------------------------------------------------------------------*/
#include "cstring.h"
#include "connect.h"
#include "session.h"

static int8_t routine_config(rqst_t *request, recv_t *receive, client_t *client) {

  //clear_restore(request, receive);
  if (browse_driver(client->protocol) <= FAIL) return EXIT;

  request->protocol = client->protocol;
  request->socket = client->socket_client;
  request->size_user = string_copy(request->user, client->user, SBUFF);   // allt detta med pekare kanske

  receive->protocol = client->protocol;
  receive->socket = client->socket_client;  
  receive->size_user = client->size_user;
  receive->size_user = string_copy(receive->user, client->user, SBUFF);

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

  rqst_t request = {0};
  recv_t receive = {0};
  int8_t control = 0;
  rout_t routine = ROUT_CONF;

  while (routine != ROUT_DONE) {                // route exit

    switch(routine) {
    case ROUT_CONF:
      control = routine_config(&request, &receive, client);
      if (control <= FAIL) {
        routine = ROUT_DONE;
      } else {
        routine = ROUT_RQST;
      }
      break;
    case ROUT_RQST:
      control = request_driver(&request);
      if (control != SUCC)
        routine = ROUT_CONF;
      else
        routine = ROUT_SEND;
      break;
    case ROUT_SEND:
      control = client_package(&request);
      if (control != SUCC)
        routine = ROUT_CONF;
      else
        routine = ROUT_RESP;
      break;
    case ROUT_RESP:
      control = server_package(&receive);
      if (control != SUCC)
        routine = ROUT_CONF;
      else
        routine = ROUT_RECV;
      break;
    case ROUT_RECV:
      control = receive_driver(&receive);
      if (control != SUCC)
        routine = ROUT_CONF;
      else
        routine = ROUT_FRWD;
      break;
    case ROUT_FRWD:
      buffer_flush(client->pack, SBUFF);
      buffer_flush(client->recv, SBUFF);
      if (receive.table_mesg) free(receive.table_mesg);
      routine = ROUT_CONF;
      break;
    default:
      System_Message("client routine fail");
      exit(EXIT_FAILURE);
    }
  }
  return control;
}

     /* for (int32_t i = 0; i < receive.amnt_rows; i++) {
        printf("ID %d \t Username: %s \t Datetime: %s \t Topic: %s \t Message: %s\n",
          receive.table_mesg[i].id, receive.table_mesg[i].user,
          receive.table_mesg[i].datm, receive.table_mesg[i].topc,
          receive.table_mesg[i].mesg
        );
      }
      */