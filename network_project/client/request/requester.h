#ifndef REQUESTER_H_
#define REQUESTER_H_

#include "../system/configs.h"

typedef struct Requester {
  int32_t sock_desc;
  uint8_t *protocol;
  size_t pack_delm;
  size_t size_user; 
  char *username;
  size_t size_datm;
  char datetime[SBUFF];
  size_t size_pack;
  char package[SBUFF];
} reqt_t;

void datetime_attach(reqt_t *request);
void protocol_attach(reqt_t *request);
void request_driver(reqt_t *requester, uint8_t *state, uint16_t *error);
void validate_pull(reqt_t *request, uint8_t *state, uint16_t *error);
void validate_push(reqt_t *request, uint8_t *state, uint16_t *error);

#endif