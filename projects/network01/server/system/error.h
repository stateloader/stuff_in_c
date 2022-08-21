#ifndef ERROR_H_
#define ERROR_H_

#include "configs.h"

#define ERROR_FORMAT "\n\t\t\tError [%s]\n\t\t\t%s\n"

typedef struct ErrorItem {
  const uint16_t flag;
  const char *type;
  const char *mesg;
} error_item;


void error_driver(uint16_t *status, uint16_t *error);

#endif

