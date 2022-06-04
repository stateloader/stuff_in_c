/*------------------------------------------------------------------------------------------------------------------------
SERVER HEADER
------------------------------------------------------------------------------------------------------------------------*/

#ifndef SERVER_H_
#define SERVER_H_

#include <stddef.h>
#include <stdint.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define SOCK 0
#define BIND 1
#define LIST 2
#define RECV 3
#define EXIT 4

#define MAX_CLIENT 8

typedef struct Session {
  size_t client_count;
  int client_size;
} sess_t;

typedef struct Server {
  uint8_t state;
  sess_t session;
  int socket_server;
  int socket_client;
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;
} serv_t;

void server_session(serv_t *server);
serv_t setup_connection(char *address, int port);

#endif
