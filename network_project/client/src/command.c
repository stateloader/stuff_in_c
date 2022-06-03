#include "scan.h"
#include "connection.h"
#include "command.h"

uint8_t static OPTION = 0x00;

static const char *OPTION_START[] = {
  "-fetch data", "-steer device", "-exit"
};
static const char *OPTION_FETCH[] = {
  "-temperature", "-humidity",
};

static const char *OPTION_STEER[] = {
  "-red", "-blue", "-green",
};

static void string_copy(char *destination, char *origin, size_t length) {			// egen modul

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

static uint8_t option_compare(char *command, char *option[], size_t arrlen) {

  for (size_t cmp = 0; cmp < arrlen; cmp++) {
    if (strcmp(command), option[i] == 0)
      return cmp;
  }
  printf("you've entered invalid command, try again!\n\n");
  return OPTION;
}

static uint8_t option_fetch(char *command, uint8_t *state) {																	// incl view

  size_t array_size = ARRAY_SIZE(OPTION_FETCH);
  scan_t scan = scan_driver("fetch phrase");
  string_copy(command, scan.scanner, scan.length);
}


static uint8_t option_steer(char *command, uint8_t *state) {

  size_t array_size = ARRAY_SIZE(OPTION_STEER);
  scan_t scan = scan_driver("steer phrase");
  string_copy(command, scan.scanner, scan.length);
}


static option_item option_items[] = {
  {option_fetch}, {option_steer}
}

static uint8_t option_start(char *command, uint8_t *state) {                      // incl view

  size_t array_size = ARRAY_SIZE(OPTION_START);
  scan_t scan = scan_driver("entry phrase");
  string_copy(command, scan.scanner, scan.length);

  return option_compare(command, OPTION_START, array_size);

}


void command_driver(char *command, uint8_t *state) {

}
