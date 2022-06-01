#include "session.h"

sess_t session_setup(char *address, int port) {

  sess_t session = {.status = 0x00};

  session.server_addr.sin_family = AF_INET;
  session.server_addr.sin_port = htons(port);
  session.server_addr.sin_addr.s_addr = inet_addr(address);

  session.socket_desc = socket(AF_INET, SOCK_STREAM, 0);

  if (session.socket_desc < 0) {
    printf("failed to create socket.\n");
    clr_bit(session.status, SOCK);

  } else {
    printf("socket created successfully.\n");
    set_bit(session.status, SOCK);
  }
  return session;
}


