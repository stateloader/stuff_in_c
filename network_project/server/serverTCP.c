/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                    SERVER
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include "socket.h"
#include "drivers/recieved.h"
#include "drivers/response.h"
#include "drivers/server.h"

static const char *GENERAL = \
  "Jacke Packe SERVER\n\n"
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore.\n"\
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore.\n"\
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore.\n";

int main(void) {
  
  Render_Header("SERVER", GENERAL);
  server_t server = {.status = 1};

  struct sockaddr_in server_address;
  struct sockaddr_in client_address;

  socket_create(&server.session.sock_serv);
  socket_bind(server.session.sock_serv, &server_address, "127.0.0.1", 90190);
  socket_listen(server.session.sock_serv);

  while(1) {
		socket_accept(server.session.sock_serv, &server.session.sock_clnt, &client_address);
    if (recieved_driver(&server) < 0)
      System_Message("Failure recieved");
    
    response_driver(&server);
    close(server.session.sock_clnt);
  }

  exit(EXIT_SUCCESS);
}