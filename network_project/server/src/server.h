#ifndef SERVER_H_
#define SERVER_H_

#include <stddef.h>
#include <stdint.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define SOCK 0
#define BIND 1
#define LIST 2
#define ACCP 3
#define RECV 4
#define EXIT 5

#define MAX_CLIENT 8
#define MAX_BUFFER 4096

typedef struct Session {
  size_t client_count;
  size_t client_lengths[MAX_CLIENT];
} sess_t;

typedef struct Connection {
  uint8_t state;
  int socket_desc;
  int connect_desc;
  sess_t session;
  struct sockaddr_in server;
  struct sockaddr_in client;
} conn_t;

typedef struct Server {
  conn_t conn;
  char strsize;
  char incoming[MAX_BUFFER];
  char outgoing[MAX_BUFFER];
} serv_t;

void server_session(serv_t *server);
conn_t setup_connection(char *address, int port, uint8_t *state);
void server_listen_accept(conn_t *conn);
