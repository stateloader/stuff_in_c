#include "src/server.h"

int main(int argc, char *argv[]) {


  serv_t server = setup_connection("127.0.0.1", 2000);
  server_session(&server);
  return 0;
}
