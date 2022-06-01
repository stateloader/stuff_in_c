#include "session.h"

sess_t session_setup(char *address, int port) {

  sess_t session;

  session.server_addr.sin_family = AF_INET;
  session.server_addr.sin_port = htons(port);
  session.server_addr.sin_addr.s_addr = inet_addr(address);
  
  session.socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  
  
  return session;
}


