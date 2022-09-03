#ifndef REQUEST__H_
#define REQUEST__H_

#include "../configs.h"

typedef struct Request {
  int32_t sock_desc;
  uint8_t *protocol;
 // size_t pack_delm;
  size_t size_user; 
  size_t size_datm;
  size_t size_pack;
  char *username;
  char datetime[SBUFF];
  char package[SBUFF];
} reqt_t;

void request_driver(reqt_t *requester);

#endif
