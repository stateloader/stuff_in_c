/*------------------------------------------------------------------------------------------------------------------------
                                                                                                            REQUEST MODULE
--------------------------------------------------------------------------------------------------------------------------
info info info info info info
------------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "command/utils/cstring.h"
#include "command/utils/scan.h"
#include "command/connect.h"
#include "command/data.h"
#include "command/device.h"
#include "command/message.h"
#include "request.h"

static const char *COMMANDS_MAIN[] = {
  "-connect", "-read data", "-steer device", "-send message", "-exit"
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

static void print_commands(const char **options, int8_t array_size) {
//desc
  printf("\t\t");
  for (int8_t i = 0; i < array_size; i++)
    printf("%s\t", options[i]);
  printf("\n");
  return;
}

static int8_t command_scanner(char *command, const char **options, int8_t array_size) {
//desc
  print_commands(options, array_size);
  
  int8_t result = 0, choice = 0, match = 0;
  scan_driver(command, CBUFF, "command");

  for (int8_t ent = 0; ent < array_size; ent++) {
    if (string_comp(command, options[ent], string_size(command, CBUFF))) {
      choice = ent, match = 1;
    }
  } if (match && current_state == MAIN) {
    result = (choice == array_size - 1) ? QUIT : choice + 1;
  } else if (match) {
    result = (choice == array_size - 1) ? MAIN : choice;
  } else {
    printf("\n%s is not an opiton, try again.\n\n", command);
    result = current_state;
  }
  buffer_flush(command, CBUFF);
  return result;
}

static int8_t command_main(char *command) {
//desc
  Print_Header("MAIN", "Navigate by enter one of the commands below.");
  return command_scanner(command, COMMANDS_MAIN, ARRAY_SIZE(COMMANDS_MAIN));
}

static int8_t command_conn(char *command) {
//desc
  Print_Header("CONNECT", "Navigate by enter one of the commands below.");

  int8_t result = 0, choice = 0;
  choice = command_scanner(command, COMMANDS_CONN, ARRAY_SIZE(COMMANDS_CONN));
    return data_driver(command, choice);
  return choice;
}

static int8_t command_data(char *command) {
//desc
  Print_Header("DATA", "Fetch data");

  int8_t result = 0, choice = 0;
  choice = command_scanner(command, COMMANDS_DATA, ARRAY_SIZE(COMMANDS_DATA));
  if (choice >= 0)
    return data_driver(command, choice);
  return choice;
}

static int8_t command_dvce(char *command) {
//desc
  Print_Header("DEVICE", "Navigate by enter one of the commands below.");

  int8_t result = 0, choice = 0;
  choice = command_scanner(command, COMMANDS_DVCE, ARRAY_SIZE(COMMANDS_DVCE));
  if (choice >= 0)
    return device_driver(command, choice);
  return choice;
}

static int8_t command_msge(char *command) {
//desc
  Print_Header("MESSAGE", "Navigate by enter one of the commands below.");

  int8_t result = 0, choice = 0;
  choice = command_scanner(command, COMMANDS_MSGE, ARRAY_SIZE(COMMANDS_MSGE));
  if (choice >= 0)
    return message_driver(command, choice);
  return choice;
}

static command_item command_items[] = {
//desc
  {command_main}, {command_conn}, {command_data},
  {command_dvce}, {command_msge},
};

uint32_t request_driver(char *request, char *command) {
//desc
  while (current_state > QUIT)
    current_state = command_items[current_state].func(command);
  current_state = MAIN;
  return string_size(command, CBUFF);
}