#include "client.h"

void print_byte(uint8_t byte) {
  for (uint8_t i = 1 << 7; i > 0; i = i / 2)
    (byte & i) ? printf("1") : printf("0");
}

static int connection(sess_t *session) {

  if (connect(session->socket, (struct sockaddr *)&session->server, sizeof(session->server)) < 0){
		printf("connection failed.\n");
    return 0;
  } else {
		printf("connection created.\n");
    set_bit(session->status, CONN);
    return 1;
  }
}

int main(void) {

  sess_t session = session_setup("127.0.0.1", 2000);
  char server_message[MAX_BUFFER], client_message[MAX_BUFFER];

  memset(server_message,'\0',sizeof(server_message));
  memset(client_message,'\0',sizeof(client_message));

  if (!connection(&session)) return - 1;

  scan_t scan = scan_driver("enter message");

  if (send(session.socket, scan.scanner, strlen(scan.scanner), 0) < 0){
      printf("Unable to send message\n");
      return -1;
  }

  if (recv(session.socket, server_message, sizeof(server_message), 0) < 0){
      printf("Error while receiving server's msg\n");
      return -1;
  }

  printf("Server's response: %s\n", server_message);

  close(session.socket);

  return 0;
}
