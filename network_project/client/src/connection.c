/*------------------------------------------------------------------------------------------------------------------------
                                                                                                         CONNECTION MODULE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/


#include "connection.h"

static void init_portip(conn_t *conn, char *address, int port) {

  conn->server.sin_family = AF_INET;
  conn->server.sin_port = htons(port);
  conn->server.sin_addr.s_addr = inet_addr(address);
}

static void init_socket(conn_t *conn) {

  conn->socket = socket(AF_INET, SOCK_STREAM, 0);

  if (conn->socket < 0) {
    printf("couldn't create socket\n\nterminating.\n");
    exit(EXIT_FAILURE);
  }
  printf("socket created.\n\n");
}

static void init_connection(conn_t *conn) {

  if (connect(conn->socket, (struct sockaddr *)&conn->server, sizeof(conn->server)) < 0) {
		printf("couldn't connect to server. sure ip and/or port is correct?\n\nterminating.");
    exit(EXIT_FAILURE);
  }
  printf("connection established.\n\n");
}

conn_t setup_connection(char *address, int port, uint8_t *state) {

  conn_t conn;

  init_portip(&conn, address, port);

  init_socket(&conn);
  *state |= (1 << SOCK);

  init_connection(&conn);
  *state |= (1 << CONN) | (1 << CMND);

  return conn;
}
