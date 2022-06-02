#include "scan.h"
#include "client.h"

static const char *TESTCMD[] = {"-add comment", "-fetch data", "-control device"};

static void comreq_checker(cent_t *client, scan_t *scan) {

  client->sizereq = scan->length;

  if (!strncpy(client->request, scan->scanner, client->sizereq))
    printf("failed to copy input from scanner.\nterminating..\n");

  if (!strncmp(client->request, scan->scanner, client->sizereq) == 0)
    printf("corrupted input copy.\nterminating..\n");

  if (!check_term(client->request, client->sizereq))
    printf("input copy not terminated.\nterminating..\n");
}

static void client_request(cent_t *client, char *message) {

  scan_t scan = scan_driver(message);
  comreq_checker(client, &scan);

  if (send(client->conn.socket, client->request, client->sizereq, 0) < 0){
    printf("couldn't sent message to server. terminating.\n");
    exit(EXIT_FAILURE);
 	}
  memset(client->request, '\0', MAX_BUFFER);
}

static void server_response(cent_t *client) {

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
