/*------------------------------------------------------------------------------------------------------------------------
                                                                                                            REQUEST MODULE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scan.h"
#include "request.h"

static const char *OPTION_START[] = {
  "-fetch data", "-steer device", "-exit"
};
static const char *OPTION_FETCH[] = {
  "-temperature", "-humidity", "-back"
};
static const char *OPTION_STEER[] = {
  "-red", "-blue", "-green", "-back"
};

static uint8_t OPTION = START;
static size_t request_size = 0;

static int8_t option_input(char *request, const char *options[], int8_t array_size) {

  request_size = scan_driver(request, MAX_BUFFER, "enter");

  for (int8_t cmp = 0; cmp < array_size; cmp++) {
    if (strcmp(request, options[cmp]) == 0)
      return cmp;
  }
  printf("you've typed an invalid command, try again!\n\n");
  return - 1;
}

static int8_t option_start(char *request) {                      						// incl view

  int8_t array_size = ARRAY_SIZE(OPTION_START);
  int8_t choice = option_input(request, OPTION_START, array_size);

  if (choice == - 1) {
    return START;
  } else if (choice == array_size - 1) {
    return LEAVE;
  } else {
    return choice + 1;
  }
}

static int8_t option_fetch(char *request) {																	// incl view

  int8_t array_size = ARRAY_SIZE(OPTION_FETCH);
  int8_t choice = option_input(request, OPTION_FETCH, array_size);

  if (choice == - 1 || choice == array_size - 1)
    return START;
  return LEAVE;
}

static int8_t option_steer(char *request) {

  int8_t array_size = ARRAY_SIZE(OPTION_STEER);
  int8_t choice = option_input(request, OPTION_STEER, array_size);

  if (choice == - 1 || choice == array_size - 1)
    return START;
  return LEAVE;
}

size_t request_driver(char *request) {

  while (OPTION != LEAVE) {

	  switch(OPTION) {

	  case START:
	    OPTION = option_start(request);
	    break;

	  case FETCH:
	    OPTION = option_fetch(request);
	    break;

	  case STEER:
	    OPTION = option_steer(request);
	    break;

	  default:
	    printf("something isn't right.\n");
	    exit(EXIT_FAILURE);
	  }
  }

  OPTION = START;
  return request_size;
}
