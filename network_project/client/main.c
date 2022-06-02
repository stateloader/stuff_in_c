#include "src/client.h"
#include "src/view.h"

static void clear_buffers(cent_t *client) {
  memset(client->request,'\0', MAX_BUFFER);
  memset(client->response,'\0', MAX_BUFFER);
}

int main(int argc, char **argv) {

  view_t views = views_create();
  cent_t client = {.view = WMENU};
  //view_driver(&client);
/*
  conn_t conn = setup_connection("127.0.0.1", 2000);
  client.conn = &conn;


  clear_buffers(&client);

  client_request(&client, "enter message from input");

  if (send(conn.socket, client.request, client.sizereq, 0) < 0){
    printf("Unable to send message\n");
    exit(0);
 	}

  if (recv(conn.socket, client.response, MAX_BUFFER, 0) < 0){
    printf("Error while receiving server's msg\n");
    exit(0);
  }

  printf("Server's response: %s\n", client.response);

  close(conn.socket);
*/
  return 0;
}
