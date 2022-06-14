/*------------------------------------------------------------------------------------------------------------------------
                                                                                                            CONNECT MODULE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include <string.h>
#include "utils/cconfig.h"
#include "utils/cerror.h"
#include "utils/cstring.h"
#include "scan.h"
#include "connect.h"

static int8_t user_login(char *username, char *password) {
  Print_Header("LOGIN", "Enter your username and password.");
  
  int8_t scan = 0;

  scan += scan_driver(username, DBUFF, "enter username");
  scan += scan_driver(password, DBUFF, "enter password");

  return scan;
}

static int8_t user_signup(char *username, char *password) {
  Print_Header("SIGNUP", "Choose username and password. Must be at least one character each.");
  
  int8_t scan = 0;

  scan += scan_driver(username, DBUFF, "choose username");
  scan += scan_driver(password, DBUFF, "choose password");

  return scan;
}

static int8_t create_connect_package(char *request, char *username, char *password, char *rcode) {

  memset(request, '\0', RBUFF);
  uint32_t ccat_buff = (string_size(username, DBUFF) + string_size(password, DBUFF)) + 1;

  strncat(request, username, ccat_buff);
  strncat(request, "|", ccat_buff);
  strncat(request, password, ccat_buff);
  strncat(request, "|", ccat_buff);
  strncat(request, rcode, ccat_buff);

  return 0;
}
int8_t connect_driver(char *request, int8_t choice) {
  
  int8_t result = 0;

  char username[DBUFF] = {'\0'};
  char password[DBUFF] = {'\0'};

  switch(choice) {
  case LOGN:
    if (user_login(username, password) == 2)
      result = create_connect_package(request, username, password, RCLO);
    else
      result = FLEE;
    break;
  case SIGU:
    if (user_signup(username, password) == 2)
      result = create_connect_package(request, username, password, RCSU);
    else
      result = FLEE;
    break;
  default:
    printf("something went horrible.\n");
    exit(EXIT_FAILURE);
  }
  return result;
}