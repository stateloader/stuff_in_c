/*------------------------------------------------------------------------------------------------------------------------
                                                                                                            CONNECT MODULE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "utils/cstring.h"
#include "utils/scanner.h"
#include "connect.h"

static int8_t connect_reader(client_t *client) {
//desc
  Print_Header("LOGIN", "Enter your username and password.");
  
  client->username_size = scan_driver(client->username, CBUFF, "username");
  client->username[client->username_size - 1] = '|';
  
  client->password_size = scan_driver(client->password, CBUFF, "password");
  client->password[client->password_size - 1] = '|';

  client->request_size = (client->username_size + client->password_size + 2);

  return SUCC;
}

static int8_t connect_request(client_t *client, int8_t choice) {
//desc
  strncat(client->request, client->username, client->request_size);
  strncat(client->request, client->password, client->request_size);

  client->username[client->username_size - 1] = '\0';
  client->password[client->password_size - 1] = '\0';

  if (choice == LOGN)
    client->request[client->request_size - 2] = RULO;
  else
    client->request[client->request_size - 2] = RUSU;
    
  uint8_t reqmask = client->request[client->request_size - 2];
  PrintByte(reqmask);
  return QUIT;
}

int8_t connect_driver(client_t *client, int8_t choice) {
  connect_reader(client);
  return connect_request(client, choice); 
}