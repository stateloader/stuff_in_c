/*------------------------------------------------------------------------------------------------------------------------
                                                                                                            COMMAND MODULE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/

#include "scan.h"
#include "connection.h"
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

static int8_t option_compare(char *command, const char *option[], int8_t array_size) {

  for (int8_t cmp = 0; cmp < array_size; cmp++) {
    if (strcmp(command, option[cmp]) == 0)
      return cmp;
  }
  printf("you've typed an invalid command, try again!\n\n");
  return - 1;
}

static int8_t option_start(char *command, size_t *return_length) {                      // incl view

  int8_t array_size = ARRAY_SIZE(OPTION_START);
  print_options("option_start", OPTION_START, array_size);

  scan_t scan = scan_driver("start phrase");
  *return_length = scan.length;

  string_copy(command, scan.scanner, scan.length);

  int8_t choice = option_compare(command, OPTION_START, array_size);

  if (choice == - 1) {
    return START;
  } else if (choice == array_size - 1) {
    return LEAVE;
  } else {
    return choice + 1;
  }
}

static int8_t option_fetch(char *command, size_t * return_length) {																	// incl view

  int8_t array_size = ARRAY_SIZE(OPTION_FETCH);
  print_options("option_fetch", OPTION_FETCH, array_size);

  scan_t scan = scan_driver("fetch phrase");

  string_copy(command, scan.scanner, scan.length);

  *return_length = scan.length;

  int8_t choice = option_compare(command, OPTION_FETCH, array_size);

  if (choice == - 1 || choice == array_size - 1)
    return START;
  return LEAVE;
}

static int8_t option_steer(char *command, size_t *return_length) {

  int8_t array_size = ARRAY_SIZE(OPTION_STEER);
  print_options("option_steer", OPTION_STEER, array_size);

  scan_t scan = scan_driver("steer phrase");

  string_copy(command, scan.scanner, scan.length);

  *return_length = scan.length;

  int8_t choice = option_compare(command, OPTION_STEER, array_size);

  if (choice == - 1 || choice == array_size - 1)
    return START;
  return LEAVE;
}

size_t command_driver(char *command, uint8_t *state) {

  size_t return_length = 0;
  memset(command, '\0', MAX_BUFFER);

  while (OPTION != LEAVE) {

    memset(command, '\0', MAX_BUFFER);

	  switch(OPTION) {

	  case START:
	    OPTION = option_start(command, &return_length);
	    break;

	  case FETCH:
	    OPTION = option_fetch(command, &return_length);
	    break;

	  case STEER:
	    OPTION = option_steer(command, &return_length);
	    break;

	  default:
	    printf("something isn't right.\n");
	    exit(EXIT_FAILURE);
	  }
  }
  OPTION = START;
  return return_length;
}
