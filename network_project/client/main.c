#include "src/client.h"

int main(int argc, char **argv) {

  cent_t client = {.state = 0x00};
  client.conn = setup_connection("127.0.0.1", 2000, &client.state);

  client.state |= (1 << CMND);
  client_session(&client);
  close(client.conn.socket);

  return 0;
}
