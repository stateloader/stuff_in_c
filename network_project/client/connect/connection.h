#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "../configs.h"

typedef struct Connection {
  int32_t bind_stat, sock_desc;
  size_t size_user, size_pass;
  char username[SBUFF];
  char password[SBUFF];
} conn_t;

void connect_driver(conn_t *connect, uint8_t *state, uint16_t *error);
void package_send(uint32_t sock_desc, char *package, size_t size_pack, uint8_t *state, uint16_t *error);
size_t package_recv(uint32_t sock_desc, char *package,  uint8_t *state, uint16_t *error);
#endif
