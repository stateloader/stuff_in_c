#include "sstring.h"
#include "validate.h"

static int8_t fetch_user_pass(vald_t *checker, server_t *server) {

  int32_t mem = 0, idx = 0;

  for (int32_t i = 0; i < server->size_pack - POFFS; i++) {
    char byte = server->pack[i];
    
    switch(mem) {
    case 0:
      if (byte != DELIM) {
        checker->comp_user[idx] = byte;
        idx++;
      } else {
        checker->comp_user[idx] = '\0';
        mem++, idx = 0;
      }
    break;
    case 1:
      if (byte != DELIM) {
        checker->comp_pass[idx] = byte;
        idx++;
      } else {
        checker->comp_pass[idx] = '\0';
        mem = 0, idx = 0;
      }
    }
  }
  Message_Info(checker->comp_user);
  Message_Info(checker->comp_pass);
  return SUCC;
}


int8_t validate_driver(server_t *server) {
  
  vald_t checker = {0};
  int8_t result = fetch_user_pass(&checker, server);
  
  return SUCC;
}
/*
static int8_t count_rows_database(check_t *checker) {

  for (int32_t i = 0; i < checker->size_data; i++)
    ckecker->amnt_delm += (check_t->[i] == DELIM) ? 1 : 0;
  checker->amnt_user = (check_t->amnt_delm / DUSER);
  return SUCC;
}
*/