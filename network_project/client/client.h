#ifndef CLIENT_H_
#define CLIENT_H_

#include <stdint.h>

#define DBUFF 64
#define FBUFF 4096
#define MBUFF 512

typedef struct Client {
  uint8_t online;
  char username[DBUFF];
  char password[DBUFF];
  char request[DBUFF];
  char message[MBUFF];
  char response[FBUFF];
} cent_t;

#endif