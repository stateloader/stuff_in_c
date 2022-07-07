#ifndef REQUESTER_H_
#define REQUESTER_H_

#include "../configs.h"

typedef struct Requester {
  uint8_t state;
  uint8_t *protocol;
  size_t pack_delm;
  size_t size_user;
  size_t size_datm;
  size_t size_ctrl;
  size_t size_pack;
  char username[SBUFF];
  char datetime[SBUFF];
  char package[SBUFF];
} reqt_t;

typedef void (*reqt_func)(reqt_t *request, uint8_t *state, uint16_t *error);

typedef struct RequestItem {
  const uint8_t table;
  reqt_func func;
} reqt_item;

void datetime_attach(reqt_t *request);
void protocol_attach(reqt_t *request);

void push_check(reqt_t *request, uint8_t *state, uint16_t *error);
void pull_check(reqt_t *request, uint8_t *state, uint16_t *error);

void request_driver(reqt_t *requester, uint8_t *state, uint16_t *error);

#endif
