/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    SERVER
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include "drivers/configs.h"
#include "drivers/socket.h"
#include "drivers/response.h"
#include "drivers/receive.h"
#include "drivers/server.h"

int main(void) {
  Render_Header("SERVER", "Lorem ipsum dolor sit amet, consectetur adipiscing elit");

  server_t server = {.status = 1};

  struct sockaddr_in server_address;
  struct sockaddr_in client_address;

  socket_create(&server.conn.sock_serv);
  socket_bind(server.conn.sock_serv, &server_address, "127.0.0.1", 90190);
  socket_listen(server.conn.sock_serv);
  
  while(server.status) {
		socket_accept(server.conn.sock_serv, &server.conn.sock_clnt, &client_address);
    receive_driver(&server);
    response_driver(&server);
    close(server.conn.sock_clnt);
  }

  exit(EXIT_SUCCESS);
}