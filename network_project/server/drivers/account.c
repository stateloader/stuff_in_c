/*------------------------------------------------------------------------------------------------------------------PARSER
                                                                                                                    
------------------------------------------------------------------------------------------------------------------------*/
#include "account.h"
#include "sstring.h"

typedef int8_t (*pars_func)(pars_t *parser);

typedef struct ParseItem {
  pars_func func;
} pars_item;

static int8_t fetch_rows(pars_t *parser) {
/*fetch amount of rows/entries in database by sniffing delims*/
  System_Message("Fetching Rows.");

  for (int32_t i = 0; i < parser->size_data; i++)
    parser->amnt_delm += (parser->data[i] == DELIM) ? 1 : 0;
  parser->amnt_rows = (parser->amnt_delm / DUSER);
  return SUCC;
}

static int8_t fetch_memo(pars_t *parser) {
/*malloc rows amount of usermodel-instances*/
  System_Message("Fetching Memory.");
  
  parser->table_user = malloc(sizeof(umod_t) * parser->amnt_rows);

  return memo_check(parser);
}

static int8_t fetch_user(pars_t *parser) {
/*fetch user credentials, the account seeking to login or being created*/
  System_Message("Fetching client credentials.");

  int32_t mem = 0, idx = 0;
  for (int32_t i = 0; i < parser->size_pack - POFFS; i++) {
    char byte = parser->pack[i];

    switch(mem) {
    case 0:
      if (byte != DELIM) {
        parser->user[idx] = byte;
        idx++;
      } else {
        parser->user[idx] = '\0';
        mem++, idx = 0;
      }
    break;
    case 1:
      if (byte != DELIM) {
        parser->pass[idx] = byte;
        idx++;
      } else {
        parser->pass[idx] = '\0';
        mem = 0, idx = 0;
      }
    }
  }
  return SUCC;
}

static int8_t fetch_tabl(pars_t *parser) {
/*fetch data to instances in user-table*/
  System_Message("Fetching data to instances of usertable from db.");

  int32_t mem = 0, idx = 0, row = 0;

  for (int32_t i = 0; i < parser->size_data; i++) {
    char byte = parser->data[i];

    switch(mem) {
    case 0:
      if (byte != DELIM) {
        parser->table_user[row].user[idx] = byte;
        idx++;
      } else {
        parser->table_user[row].user[idx] = '\0';
        mem++, idx = 0;
      }
    break;
    case 1:
      if (byte != DELIM) {
        parser->table_user[row].pass[idx] = byte;
        idx++;
      } else {
        parser->table_user[row].pass[idx] = '\0';
        mem = 0, idx = 0, row++;
      }
    }
  }
  return SUCC;
}

static int8_t valid_user(pars_t *parser, int32_t i) {
  if (string_comp(parser->user, parser->table_user[i].user, SBUFF))
    return SUCC;
  return FAIL;
}

static int8_t valid_pass(pars_t *parser, int32_t i) {
  if (string_comp(parser->pass, parser->table_user[i].pass, SBUFF))
    return SUCC;
  return FAIL;
}

static int8_t parse_logn(pars_t *parser) {
/*compare user/pass from current database (table), poly-match and it's a hit.*/

  System_Message("Parsing login-credentials.");

  int8_t match = 0;
  for (int32_t i = 0; i < parser->amnt_rows; i++)
    match += (valid_user(parser, i) == SUCC && valid_pass(parser, i) == SUCC) ? 1 : 0;
  
  if (match) {
    parser->protocol[SBYTE] |= (1 << VALID);
    System_Message("user credentials valid.");
  } else {
    System_Message("user credentials invalid.");
  }
  if (parser->table_user) free(parser->table_user);
  return SUCC;
}

static int8_t parse_setp(pars_t *parser) {
/*compare username during acc-setup, if not taken it's a hit*/

  System_Message("Parsing setup-credentials.");

  int8_t taken = 0;
  for (int32_t i = 0; i < parser->amnt_rows; i++)
    taken += (valid_user(parser, i) ==  SUCC) ? 1 : 0;
  
  if (!taken) {
    System_Message("username not taken.");
    parser->protocol[SBYTE] |= (1 << VALID);
  } else {
    parser->protocol[SBYTE] ^= (1 << SETUP);
    System_Message("username already taken.");
  }

  if (parser->table_user) free(parser->table_user);
  return SUCC;
}

static pars_item parse_items[] = {
  {fetch_rows}, {fetch_memo}, {fetch_user}, {fetch_tabl}
};

int8_t account_driver(pars_t *parser) {
  System_Message("INIT ACCOUNT PARSING\n");

  for (size_t i = 0; i < ARRAY_SIZE(parse_items); i++) {
    if (!parse_items[i].func(parser))
      return FAIL;
  }
  System_Message("efter inits");
  if (parser->protocol[SBYTE] & (1 << LOGIN))
    return parse_logn(parser);
  else if (parser->protocol[SBYTE] & (1 << SETUP)) 
    return parse_setp(parser);
  else
    return FAIL;
}