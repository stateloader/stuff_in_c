#ifndef CLIENT_H_
#define CLIENT_H_

#include "config.h"
#include "socket.h"

typedef struct Connection {
  struct sockaddr_in server_address;
  int32_t socket_status;
  int32_t socket_client;
} conn_t;

typedef struct Client {
  conn_t conn;
  uint8_t protocol[3];
  int32_t size_send;
  int32_t size_user;
  int32_t size_pass;
  int32_t size_pack;
  int32_t size_recv;
  char user[SBUFF];
  char pass[SBUFF];
} client_t;

#endif