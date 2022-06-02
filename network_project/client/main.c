#include "src/client.h"

// argc n argv fix.

int main(int argc, char **argv) {

  cent_t client;
  client.conn = setup_connection("127.0.0.1", 2000);
  client_session(&client);

  return 0;
}
