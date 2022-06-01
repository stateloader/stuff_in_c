#ifndef SESSION_H_
#define SESSION_H_

#include "../scan/scan.h"
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SOCK 0

#define set_bit(byte, bit) byte |= (1 << bit)
#define get_bit(byte, bit) byte &= (1 << bit)
#define tog_bit(byte, bit) byte ^= (1 << bit)
#define clr_bit(byte, bit) byte &= ~(1 << bit)

typedef struct Session {
  uint8_t status;
  int socket_desc;
  struct sockaddr_in server_addr;
} sess_t;

sess_t session_setup(char *address, int port);

#endif
