/*------------------------------------------------------------------------------------------------------------------------
                                                                                                            CONNECT MODULE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include <string.h>
#include "utils/cerror.h"
#include "utils/cstring.h"
#include "utils/scan.h"
#include "connect.h"

static void userdata(client_t *client) {
  
  Print_Header("LOGIN", "Enter your username and password.");
  
  client->username_size = scan_driver(client->username, CBUFF, "enter username");
  client->username[client->username_size - 1] = '|';
  
  client->password_size = scan_driver(client->password, CBUFF, "enter password");
  client->password[client->password_size - 1] = '|';
  
  client->request_size = (client->username_size + client->password_size + 2);
}

static int8_t connect_package(client_t *client) {
  
  strncat(client->request, client->username, client->request_size);
  strncat(client->request, client->password, client->request_size);

  client->request[client->request_size - 2] = 0b00000001;

  uint8_t check_bit = 0;
  uint8_t reqmask = client->request[client->request_size - 2];
  
  while (check_bit < 8) {
    if (reqmask & 0x01)
      printf("1\n");
    else
      printf("0\n");
    check_bit++;
    reqmask = reqmask >> 1;
  }
  printf("string: client->request: %s\n", client->request);
  return QUIT;
}

int8_t connect_driver(client_t *client, int8_t choice) {
  
  userdata(client);
  if (choice == LOGN)
    return connect_package(client);
  else
    return connect_package(client);
}