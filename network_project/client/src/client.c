#include "client.h"

static void request_checker(cent_t *client, scan_t *scan) {

  client->sizereq = scan->length;

  char *cpy_result = strncpy(client->request, scan->scanner, client->sizereq);
  if (!cpy_result) printf("error strncpy.\n");

  size_t cmp_result = strncmp(client->request, scan->scanner, client->sizereq);
  if (cmp_result != 0) printf("error strncmp.\n");

}

static void client_request(cent_t *client, char *message) {

  scan_t scan = scan_driver(message);
  request_checker(client, &scan);

  if (send(client->conn.socket, client->request, client->sizereq, 0) < 0){
    printf("couldn't sent message to server. terminating.\n");
    exit(0);
 	}
  memset(client->request, '\0', MAX_BUFFER);
}

static void server_response(cent_t * client) {

  if (recv(client->conn.socket, client->response, MAX_BUFFER, 0) < 0){
    printf("couldn't recieve server message. terminating.");
    exit(0);
  }
  printf("from server: %s\n", client->response);
  memset(client->response, '\0', MAX_BUFFER);
}

void client_session(cent_t *client) {

  client_request(client, "skriv natt kul: ");
  server_response(client);

  close(client->conn.socket);
}
