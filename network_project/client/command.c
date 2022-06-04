/*------------------------------------------------------------------------------------------------------------------------
                                                                                                            COMMAND MODULE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scan.h"
#include "command.h"


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

static int8_t option_input(char *command, const char *options[], int8_t array_size, size_t *command_length) {

  print_options("option_start", options, array_size);

  memset(command, '\0', MAX_BUFFER);
  scan_t scan = scan_driver("enter command phrase");
  string_copy(command, scan.scanner, scan.length);
  *command_length = scan.length;

  for (int8_t cmp = 0; cmp < array_size; cmp++) {
    if (strcmp(command, options[cmp]) == 0)
      return cmp;
  }
  printf("you've typed an invalid command, try again!\n\n");
  return - 1;
}

static int8_t option_start(char *command, size_t *command_length) {                      // incl view

  int8_t array_size = ARRAY_SIZE(OPTION_START);
  int8_t choice = option_input(command, OPTION_START, array_size, command_length);
  if (choice == - 1) {
    return START;
  } else if (choice == array_size - 1) {
    return LEAVE;
  } else {
    return choice + 1;
  }
}

static int8_t option_fetch(char *command, size_t *command_length) {																	// incl view

  int8_t array_size = ARRAY_SIZE(OPTION_FETCH);
  int8_t choice = option_input(command, OPTION_FETCH, array_size, command_length);
  if (choice == - 1 || choice == array_size - 1)
    return START;
  return LEAVE;
}

static int8_t option_steer(char *command, size_t *command_length) {

  int8_t array_size = ARRAY_SIZE(OPTION_STEER);
  int8_t choice = option_input(command, OPTION_STEER, array_size, command_length);
  if (choice == - 1 || choice == array_size - 1)
    return START;
  return LEAVE;
}

int command_driver(char *command) {

  size_t command_length = 0;

  while (OPTION != LEAVE) {

	  switch(OPTION) {

	  case START:
	    OPTION = option_start(command, &command_length);
	    break;

	  case FETCH:
	    OPTION = option_fetch(command, &command_length);
	    break;

	  case STEER:
	    OPTION = option_steer(command, &command_length);
	    break;

	  default:
	    printf("something isn't right.\n");
	    exit(EXIT_FAILURE);
	  }
  }
  OPTION = START;
  return (int) command_length;
}
