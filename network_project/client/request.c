/*------------------------------------------------------------------------------------------------------------------------
                                                                                                            COMMAND MODULE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scan.h"
#include "request.h"


static uint8_t OPTION = START;

static const char *OPTION_START[] = {
  "-fetch data", "-steer device", "-exit"
};
static const char *OPTION_FETCH[] = {
  "-temperature", "-humidity", "-back"
};
static const char *OPTION_STEER[] = {
  "-red", "-blue", "-green", "-back"
};

static void print_options(char *option, const char *options[], int8_t array_size) {

  printf("inside :%s\n\n", option);
  for (int8_t i = 0; i < array_size; i++)
    printf("%s\n", options[i]);
  printf("\n");
}

static void string_copy(char *destination, char *origin, size_t length) {

  if (!strncpy(destination, origin, length)) {
    printf("failed to copy input from scanner.\nterminating..\n");
    exit(EXIT_FAILURE);

  } else if (!strncmp(destination, origin, length) == 0) {
    printf("corrupted input copy.\nterminating..\n");
    exit(EXIT_FAILURE);

  } else if (!check_term(destination, length)) {
    printf("input copy not terminated.\nterminating..\n");
    exit(EXIT_FAILURE);
  }
}

static int8_t option_input(char *request, const char *options[], int8_t array_size, size_t *request_length) {

  print_options("option_start", options, array_size);

  memset(request, '\0', MAX_BUFFER);
  scan_t scan = scan_driver("enter command phrase");
  string_copy(request, scan.scanner, scan.length);
  *request_length = scan.length;

  for (int8_t cmp = 0; cmp < array_size; cmp++) {
    if (strcmp(request, options[cmp]) == 0)
      return cmp;
  }
  printf("you've typed an invalid command, try again!\n\n");
  return - 1;
}

static int8_t option_start(char *request, size_t *request_length) {                      // incl view

  int8_t array_size = ARRAY_SIZE(OPTION_START);
  int8_t choice = option_input(request, OPTION_START, array_size, request_length);
  if (choice == - 1) {
    return START;
  } else if (choice == array_size - 1) {
    return LEAVE;
  } else {
    return choice + 1;
  }
}

static int8_t option_fetch(char *request, size_t *request_length) {																	// incl view

  int8_t array_size = ARRAY_SIZE(OPTION_FETCH);
  int8_t choice = option_input(request, OPTION_FETCH, array_size, request_length);
  if (choice == - 1 || choice == array_size - 1)
    return START;
  return LEAVE;
}

static int8_t option_steer(char *request, size_t *request_length) {

  int8_t array_size = ARRAY_SIZE(OPTION_STEER);
  int8_t choice = option_input(request, OPTION_STEER, array_size, request_length);
  if (choice == - 1 || choice == array_size - 1)
    return START;
  return LEAVE;
}

int request_driver(char *request) {

  size_t request_length = 0;

  while (OPTION != LEAVE) {

	  switch(OPTION) {

	  case START:
	    OPTION = option_start(request, &request_length);
	    break;

	  case FETCH:
	    OPTION = option_fetch(request, &request_length);
	    break;

	  case STEER:
	    OPTION = option_steer(request, &request_length);
	    break;

	  default:
	    printf("something isn't right.\n");
	    exit(EXIT_FAILURE);
	  }
  }
  OPTION = START;
  return (int) request_length;
}
