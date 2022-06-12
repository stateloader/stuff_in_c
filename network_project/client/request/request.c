/*------------------------------------------------------------------------------------------------------------------------
                                                                                                            REQUEST MODULE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cstring.h"
#include "scan.h"
#include "command.h"
#include "request.h"

static const char *REQUEST_START[] = {
  "-fetch data", "-steer device", "-make comment", "-logout"
};
static const char *REQUEST_FETCH[] = {
  "-temp", "-back"
};
static const char *REQUEST_STEER[] = {
  "-red", "-blue", "-green", "-back"
};

static uint8_t MENU = START;
static size_t request_size = 0;

static int8_t request_scanner(char *request, const char *commands[], int8_t array_size) {

  request_size = scan_driver(request, MAX_BUFFER, "enter");

  for (int8_t cmp = 0; cmp < array_size; cmp++) {
    if (strcmp(request, commands[cmp]) == 0)
      return cmp;
  }
  printf("you've typed an invalid command, try again!\n\n");
  return - 1;
}

static int8_t request_start(char *request) {

  int8_t array_size = ARRAY_SIZE(REQUEST_START);
  int8_t choice = request_scanner(request, REQUEST_START, array_size);

  if (choice == - 1) {
    return START;
  } else if (choice == array_size - 1) {
    return LEAVE;
  } else {
    return choice + 1;
  }
}

static int8_t request_fetch(char *request) {

  int8_t array_size = ARRAY_SIZE(REQUEST_FETCH);
  int8_t choice = request_scanner(request, REQUEST_FETCH, array_size);

  if (choice == - 1 || choice == array_size - 1)
    return START;
  return LEAVE;
}

static int8_t request_steer(char *request) {

  int8_t array_size = ARRAY_SIZE(REQUEST_STEER);
  int8_t choice = request_scanner(request, REQUEST_STEER, array_size);

  if (choice == - 1 || choice == array_size - 1)
    return START;
  return LEAVE;
}

size_t request_driver(char *request, uint8_t *online) {

  MENU = (!*online) ? command_driver(request, online) : START;

  while (MENU != LEAVE) {

	  switch(MENU) {
    
	  case START:
	    MENU = request_start(request);
	    break;

	  case FETCH:
	    MENU = request_fetch(request);
	    break;

	  case STEER:
	    MENU = request_steer(request);
	    break;

	  default:
	    printf("something isn't right.\n");
	    exit(EXIT_FAILURE);
	  }
  }

  return request_size;
}
