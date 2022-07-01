/*-----------------------------------------------------------------------------------------------------------PARSER HEADER
                                                                                                                    
------------------------------------------------------------------------------------------------------------------------*/
#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include "controller.h"

typedef struct UserModel {
  char user[SBUFF];
  char pass[SBUFF];
} umod_t;

typedef struct Parser {
  uint8_t protocol[3];
  int32_t amnt_delm;
  int32_t amnt_rows;
  int32_t size_user;
  int32_t size_pass;
  int32_t size_pack;
  int32_t size_data;
  char user[SBUFF];
  char pass[SBUFF];
  char pack[SBUFF];
  char data[SBUFF];
  umod_t *table_user;
} pars_t;

int8_t account_driver(pars_t *parser);
//-----------------------------------------------------------------------------------------------------PARSER ERROR CHECKS
inline static uint8_t rows_check(pars_t *parser) {
  return SUCC;
}
inline static uint8_t memo_check(pars_t *parser) {
  if (parser->table_user == NULL) {
    System_Message("Memory error while creating user-instances.");
    return FAIL;
  }
  return SUCC;
}

inline static uint8_t user_check(pars_t *parser) {
  if (parser->user == NULL || parser->pass == NULL) {
    System_Message("Member error parseble data in user and/or pass-member.");
    return FAIL;
  }
  return SUCC;
}
#endif