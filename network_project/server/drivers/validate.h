#ifndef VALIDATE_H_
#define VALIDATE_H_

#include "configs.h"
#include "server.h"

#define _USER 0
#define _PASS 1
#define _DONE 2

typedef struct UserModel {
  char known_user[SBUFF];
  char known_pass[SBUFF];
} umod_t;

typedef struct Validation{
  int32_t amnt_delm;
  int32_t amnt_user;
  int32_t size_user;
  int32_t size_pass;
  char comp_user[SBUFF];
  char comp_pass[SBUFF];
  umod_t *table_user;
} vald_t;

int8_t validate_driver(server_t *server);

#endif