/*------------------------------------------------------------------------------------------------------------------------
                                                                                                                   CONNECT
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "cstring.h"
#include "scanner.h"
#include "connect.h"

static int8_t connect_reader(client_t *client) {
//desc
  Render_Header("LOGIN", "Enter your username and password.");

  client->size_user = scan_driver(client->user, CBUFF, "username");
  client->user[client->size_user - 1] = '|';

  client->size_pass = scan_driver(client->pass, CBUFF, "password");
  client->pass[client->size_pass - 1] = '|';

  client->size_rqst = (client->size_user + client->size_pass + 2);

  return connect_reader_check(client);
}

static int8_t connect_binder(client_t *client, int8_t choice) {
//desc

  strncat(client->rqst, client->user, client->size_rqst);
  strncat(client->rqst, client->pass, client->size_rqst);

  client->user[client->size_user - 1] = '\0';
  client->pass[client->size_pass - 1] = '\0';

  if (choice == LOGN)
    client->rqst[client->size_rqst - 2] = RULO;//                                             Request User Login Bit
  else
    client->rqst[client->size_rqst - 2] = RUSU;//                                            Request User Signup Bit
  
  return connect_binder_check(client);
}

int8_t connect_driver(client_t *client, int8_t choice) {

  if (connect_reader(client) < 0)
    return FLEE;
  else
    return connect_binder(client, choice);
}