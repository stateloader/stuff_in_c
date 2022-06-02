#include "src/connection.h"

static void clear_buffers(conn_t *conn) {
  memset(conn->client.request,'\0', MAX_BUFFER);
  memset(conn->client.response,'\0', MAX_BUFFER);
}

int main(int argc, char **argv) {

  conn_t conn = setup_connection("127.0.0.1", 2000);

  clear_buffers(&conn);

  client_request(&conn.client, "enter message from input");

  if (send(conn.socket, conn.client.request, conn.client.sizereq, 0) < 0){
    printf("Unable to send message\n");
    exit(0);
 	}

  if (recv(conn.socket, conn.client.response, MAX_BUFFER, 0) < 0){
    printf("Error while receiving server's msg\n");
    exit(0);
  }

  printf("Server's response: %s\n", conn.client.response);

  close(conn.socket);

  return 0;
}
