/*------------------------------------------------------------------------------------------------------------------------
                                                                                                            REQUEST MODULE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scan.h"
#include "cstring.h"
#include "request.h"

#include <stdint.h>

static const char *REQUEST_CONN[] = {
  "-login", "-signup", "-exit"
};
static const char *REQUEST_MAIN[] = {
  "-read data", "-steer device", "-make comment", "-logout"
};
static const char *REQUEST_DATA[] = {
  "-temp", "-back"
};
static const char *REQUEST_DVCE[] = {
  "-red", "-blue", "-green", "-back"
};

static uint8_t state = MAIN;
static size_t request_size = 0;

static int8_t request_encode(char *request) {
  printf("request: %s\n", request);
  return SUCC;
}

static uint8_t load_request_view(char *item, const char **options, uint8_t array_size) {

  Print_View_Item(item);
  printf("\t");
  for (uint8_t i = 0; i < array_size; i++)
    printf("%s\t", options[i]);
  printf("\n\n");

  return array_size;
}

static int8_t request_scanner(char *request, const char **options, int8_t array_size) {

  request_size = scan_driver(request, RBUFF, "submit");

  for (int8_t cmp = 0; cmp < array_size; cmp++) {
    if (string_comp(request, options[cmp], request_size))
      return cmp;
  }
  Info_Message(request, "is not an option, try again.");
  return - 1;
}

static int8_t user_connect(char *request, uint8_t choice) {

  char *username[DBUFF] = {'\0'};
  char *password[DBUFF] = {'\0'};

  switch(choice) {

  case LOGN:
    Print_View_Item("LOGIN");
    break;
  case SIGU:
    Print_View_Item("SIGNUP");
    break;
  default:
    printf("something isn't right.\n");
    exit(EXIT_FAILURE);
  }

  return EXIT;
}

static int8_t request_conn(char *request) {

  int8_t array_size = ARRAY_SIZE(REQUEST_CONN);
  load_request_view(Conn_View, REQUEST_CONN, array_size);

  int8_t choice = request_scanner(request, REQUEST_CONN, array_size);

  if (choice == - 1)
    return CONN;

  else if (choice == LOGN || choice == SIGU)
    return user_connect(request, choice);
  else if (choice == array_size - 1)
    return EXIT;
  else
    return choice + 1;
}

static int8_t request_main(char *request) {

  int8_t array_size = ARRAY_SIZE(REQUEST_MAIN);
  int8_t choice = request_scanner(request, REQUEST_MAIN, array_size);

  if (choice == - 1)
    return MAIN;
  else if (choice == array_size - 1)
    return EXIT;
  else
    return choice + 1;
}

static int8_t request_data(char *request) {

  int8_t array_size = ARRAY_SIZE(REQUEST_DATA);
  int8_t choice = request_scanner(request, REQUEST_DATA, array_size);

  if (choice == - 1 || choice == array_size - 1)
    return MAIN;
  return EXIT;
}

static int8_t request_dvce(char *request) {

  int8_t array_size = ARRAY_SIZE(REQUEST_DVCE);
  int8_t choice = request_scanner(request, REQUEST_DVCE, array_size);

  if (choice == - 1 || choice == array_size - 1)
    return MAIN;
  return EXIT;
}

static int8_t request_msge(char *request) {

  int8_t array_size = ARRAY_SIZE(REQUEST_DVCE);
  int8_t choice = request_scanner(request, REQUEST_DVCE, array_size);

  if (choice == - 1 || choice == array_size - 1)
    return MAIN;
  return EXIT;
}

uint32_t request_driver(char *request, uint8_t *online) {

  if (!*online) state = CONN;
  while (state != EXIT) {

	  switch(state) {
    case CONN:
	    state = request_conn(request);
	    break;
	  case MAIN:
	    state = request_main(request);
	    break;
	  case DATA:
	    state = request_data(request);
	    break;
	  case DVCE:
	    state = request_dvce(request);
      break;
	  case MSGE:
	    state = request_msge(request);
	    break;
	  default:
	    printf("something isn't right.\n");
	    exit(EXIT_FAILURE);
	  }
  }

  return request_size;
}