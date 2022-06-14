/*------------------------------------------------------------------------------------------------------------------------
                                                                                                            REQUEST MODULE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "utils/cstring.h"
#include "utils/scan.h"
#include "commit/connect.h"
#include "commit/data.h"
#include "commit/device.h"
#include "commit/message.h"
#include "request.h"

static const char *COMMANDS_MAIN[] = {
  "-connect, -read data", "-steer device", "-send message", "-exit"
};
static const char *COMMANDS_CONN[] = {
  "-login", "-signup", "-main"
};
static const char *COMMANDS_DATA[] = {
  "-read temp", "-read messages", "-main"
};
static const char *COMMANDS_DVCE[] = {
  "-red", "-blue", "-green", "-main"
};
static const char *COMMANDS_MSGE[] = {
  "-send", "-main"
};

static int8_t current_state = MAIN;

static void print_commands(const char **options, uint32_t array_size) {
  printf("\t\t");
  for (uint32_t i = 0; i < array_size; i++)
    printf("%s\t", options[i]);
  printf("\n");
  return;
}

static int8_t command_scanner(char *command, const char **options, uint32_t array_size) {
  print_commands(options, array_size);
  
  int8_t result = 0, choice = 0, match = 0;
  scan_driver(command, RBUFF, "command");

  for (uint32_t ent = 0; ent < array_size; ent++) {
    if (string_comp(command, options[ent], string_size(command, DBUFF))) {
      choice = ent, match = 1;
    }
  } if (match && current_state == MAIN) {
    result = (choice == array_size - 1) ? QUIT : choice;
  } else if (match) {
    result = (choice == array_size - 1) ? MAIN : choice;
  } else {
    printf("\n%s is not an opiton, try again.\n\n", command);
    result = current_state;
  }
  buffer_flush(command, MBUFF);
  return result;
}

static int8_t command_main(char *command) {
  Print_Header("MAIN", "Navigate by enter one of the commands below.");

  int8_t result = 0, choice = 0;
  choice = command_scanner(command, COMMANDS_MAIN, ARRAY_SIZE(COMMANDS_MAIN));

}

static int8_t command_conn(char *command) {
  Print_Header("CONNECT", "Navigate by enter one of the commands below.");

  int8_t result = 0, choice = 0;
  choice = command_scanner(command, COMMANDS_CONN, ARRAY_SIZE(COMMANDS_CONN));

}

static int8_t command_data(char *command) {
  Print_Header("DATA", "Fetch data");

  int8_t result = 0, choice = 0;
  choice = command_scanner(command, COMMANDS_DATA, ARRAY_SIZE(COMMANDS_DATA));
}

static int8_t command_dvce(char *command) {
  Print_Header("DEVICE", "Navigate by enter one of the commands below.");

  int8_t result = 0, choice = 0;
  choice = command_scanner(command, COMMANDS_DVCE, ARRAY_SIZE(COMMANDS_DVCE));
}

static int8_t command_msge(char *command) {
  Print_Header("MESSAGE", "Navigate by enter one of the commands below.");

  int8_t result = 0, choice = 0;
  choice = command_scanner(command, COMMANDS_MSGE, ARRAY_SIZE(COMMANDS_MSGE));
}

static command_item command_items[] = {
  {command_main}, {command_conn}, {command_data},
  {command_dvce}, {command_msge},
};

uint32_t request_driver(char *request, char *command) {

  while (current_state != QUIT)
    current_state = command_items[current_state].func(command);
  return 7;
}