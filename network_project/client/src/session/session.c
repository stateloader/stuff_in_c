#include "session.h"

static void setsocket(sess_t *session) {

  session->socket = socket(AF_INET, SOCK_STREAM, 0);

  if (session->socket < 0) {
    printf("failed to create socket.\n");
    clr_bit(session->status, SOCK);

  } else {
    printf("socket created successfully.\n");
    set_bit(session->status, SOCK);
  }
}

sess_t session_setup(char *address, int port) {

  sess_t session = {.status = 0x00};

  session.server.sin_family = AF_INET;
  session.server.sin_port = htons(port);
  session.server.sin_addr.s_addr = inet_addr(address);

  setsocket(&session);

  return session;
}


