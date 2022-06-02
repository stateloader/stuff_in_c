#ifndef CLIENT_H_
#define CLIENT_H_

#include "scan.h"

typedef struct Client {
  size_t sizereq, sizeres;
  char request[MAX_BUFFER];		//reqcmnd
  char response[MAX_BUFFER];  //resmesg
} cent_t;


void client_request(cent_t *client, char *message);

#endif
