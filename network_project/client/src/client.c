#include "client.h"

static void connection(sess_t *session) {

  if (connect(session->socket, (struct sockaddr *)&session->server, sizeof(session->server)) < 0) {
		printf("connection failed.\n");
    exit(0);
  } else {
		printf("connection created.\n");
    set_bit(session->status, CONN);
  }
}

int main(int argc, char **argv) {

  sess_t session = session_setup("127.0.0.1", 2000);
  connection(&session);
 // cent_t client;

  char server_message[MAX_BUFFER], client_message[MAX_BUFFER];

  memset(server_message,'\0',sizeof(server_message));
  memset(client_message,'\0',sizeof(client_message));

  scan_t scan = scan_driver("enter message");

  if (send(session.socket, scan.scanner, strlen(scan.scanner), 0) < 0){
    printf("Unable to send message\n");
    exit(0);
 	}

  if (recv(session.socket, server_message, sizeof(server_message), 0) < 0){
    printf("Error while receiving server's msg\n");
    exit(0);
  }

  printf("Server's response: %s\n", server_message);

  close(session.socket);

  return 0;
}
/*
void print_byte(uint8_t byte) {
  for (uint8_t i = 1 << 7; i > 0; i = i / 2)
    (byte & i) ? printf("1") : printf("0");
}
*/
