#ifndef REQUESTER_H_
#define REQUESTER_H_

#include "../system/configs.h"

typedef struct Requester {
  int32_t sock_desc;
  uint8_t protocol[3];
  size_t pack_delm;
  size_t size_ctrl;
  size_t size_user;
  char username[SBUFF];
  size_t size_datm;
  char datetime[SBUFF];
  size_t size_pack;
  char package[SBUFF];
} reqt_t;

typedef void (*reqt_func)(reqt_t *request, uint8_t *state, uint16_t *error);

typedef struct RequestItem {
  const uint8_t table;
  reqt_func func;
} reqt_item;

void datetime_attach(reqt_t *request);
void protocol_attach(reqt_t *request);

void writer_validate(reqt_t *request, uint8_t *state, uint16_t *error);
void reader_validate(reqt_t *request, uint8_t *state, uint16_t *error);

void request_driver(reqt_t *requester, uint8_t *state, uint16_t *error);

#endif
