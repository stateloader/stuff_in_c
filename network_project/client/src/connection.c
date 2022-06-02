#include "connection.h"

static void init_portip(conn_t *conn, char *address, int port) {

  conn->server.sin_family = AF_INET;
  conn->server.sin_port = htons(port);
  conn->server.sin_addr.s_addr = inet_addr(address);
}

static void init_socket(conn_t *conn) {

  conn->socket = socket(AF_INET, SOCK_STREAM, 0);

  if (conn->socket < 0) {
    printf("socket error.\n");
    exit(0);
  } else {
    printf("socket created.\n");
    set_bit(conn->status, SOCK);
  }
}

static void init_connection(conn_t *conn) {

  if (connect(conn->socket, (struct sockaddr *)&conn->server, sizeof(conn->server)) < 0) {
		printf("connection error.\n");
    exit(0);
  } else {
		printf("connection established.\n");
    set_bit(conn->status, CONN);
  }
}

conn_t setup_connection(char *address, int port) {

  conn_t conn = {.status = 0x00};

  init_portip(&conn, address, port);
  init_socket(&conn);
  init_connection(&conn);

  return conn;
}
