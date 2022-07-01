#include "socket.h"
#include "response.h"
#include "receive.h"
#include "server.h"
#include "session.h"

int8_t session_driver(server_t *server, char *address, int32_t port) {

  struct sockaddr_in server_address;
  struct sockaddr_in client_address;

  socket_create(&server->conn.sock_serv);
  socket_binder(server->conn.sock_serv, &server_address, address, port);
  socket_listen(server->conn.sock_serv);

  int8_t result = 0;

  while(server->session & (1 << ALIVE)) {
		socket_accept(server->conn.sock_serv, &server->conn.sock_clnt, &client_address);
    result = receive_driver(server);
    response_driver(server, result);
    close(server->conn.sock_clnt);
  }
  exit(EXIT_FAILURE);
}