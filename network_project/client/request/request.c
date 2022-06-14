/*------------------------------------------------------------------------------------------------------------------------
                                                                                                            REQUEST MODULE
--------------------------------------------------------------------------------------------------------------------------
Attempt in creating some kind of command-driven interface. 
------------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "command/utils/cstring.h"
#include "command/utils/scanner.h"
#include "command/connect.h"
#include "command/fetcher.h"
#include "command/device.h"
#include "command/message.h"
#include "request.h"

static const char *COMMANDS_MAIN[] = {
  "-connect", "-read data", "-steer device", "-send message", "-exit"
};
static const char *COMMANDS_CONN[] = {
  "-main", "-login", "-signup"
};
static const char *COMMANDS_DATA[] = {
  "-main", "-read temp", "-read messages"
};
static const char *COMMANDS_DVCE[] = {
  "-main", "-red", "-blue", "-green"
};
static const char *COMMANDS_MSGE[] = {
  "-main", "-send"
};
//String arrays storing allowed commands.

static int8_t current_state = MAIN;

static void print_commands(const char **options, int8_t array_size) {
//Prints unique oftions (given current state).

  printf("\t\t");
  for (int8_t i = 0; i < array_size; i++)
    printf("%s\t", options[i]);
  printf("\n");
  return;
}

static int8_t command_scanner(char *command, const char **options, int8_t array_size) {
//User enter one of the options before this input being checked (must match one of them).

  print_commands(options, array_size);
  
  int8_t result = 0, choice = 0, match = 0;
  scan_driver(command, CBUFF, "command");

  for (int8_t ent = 0; ent < array_size; ent++) {
    if (string_comp(command, options[ent], string_size(command, CBUFF))) {
      choice = ent, match = 1;
    }
  } if (match && current_state == MAIN) {
    result = (choice == array_size - 1) ? QUIT : choice + 1;
  } else if (match  && current_state != MAIN) {
    result = choice;
  } else {
    printf("\n%s is not an option, try again.\n\n", command);
    result = current_state;
  }

//If there's a match and 'current_state' is 'MAIN' - and the last option is choosen - it means QUIT, otherwise a
//specific entry has been choosen [conn, data, device, message (and perhaps future ones)]. If so, 'choice'
//increments by 1 to map with the list of 'command_items' (SEE bottom).

//If there's a match and we're not in 'MAIN' we'll head to a specific driver (SEE <namn>-folder) for some final
//treatment before wishing our request bon voyage. No match (the user went medieval in the keyboard or something)
//and the current state being called again.

  buffer_flush(command, CBUFF);
  return result;
}

static int8_t command_main(client_t *client) {
//return result from 'command_scanner'.

  Print_Header("MAIN", "Lorem ipsum dolor sit amet, consectetur adipiscing elit");
  return command_scanner(client->command, COMMANDS_MAIN, ARRAY_SIZE(COMMANDS_MAIN));
}

static int8_t command_conn(client_t *client) {
//return choce from 'command_scanner', if legit return the result from 'connect_driver'.

  Print_Header("CONNECT", "Lorem ipsum dolor sit amet, consectetur adipiscing elit");

  int8_t choice = command_scanner(client->command, COMMANDS_CONN, ARRAY_SIZE(COMMANDS_CONN));
  if (choice > 0)
    return connect_driver(client, choice - 1);
  return choice;
}

static int8_t command_data(client_t *client) {
//return choice from 'command_scanner', if legit return the result from 'data_driver'.

  Print_Header("DATA", "Lorem ipsum dolor sit amet, consectetur adipiscing elit");

  int8_t choice = command_scanner(client->command, COMMANDS_DATA, ARRAY_SIZE(COMMANDS_DATA));
  if (choice > 0)
    return fetch_driver(client, choice - 1);
  return choice;
}

static int8_t command_dvce(client_t *client) {
//return choice from 'command_scanner', if legit return the result from 'device_driver'.

  Print_Header("DEVICE", "Lorem ipsum dolor sit amet, consectetur adipiscing elit");

  int8_t choice = command_scanner(client->command, COMMANDS_DVCE, ARRAY_SIZE(COMMANDS_DVCE));
  if (choice > 0)
    return device_driver(client, choice - 1);
  return choice;
}

static int8_t command_mesg(client_t *client) {
//return choice from 'command_scanner', if legit return the result from 'message_driver'.

  Print_Header("MESSAGE", "Lorem ipsum dolor sit amet, consectetur adipiscing elit");

  int8_t choice = command_scanner(client->command, COMMANDS_MSGE, ARRAY_SIZE(COMMANDS_MSGE));
  if (choice > 0)
    return message_driver(client);
  return choice;
}

static command_item command_items[] = {
//item-list of functions being called upon based on index.

  {command_main}, {command_conn}, {command_data},
  {command_dvce}, {command_mesg},
};

int8_t request_driver(client_t *client) {
//desc

  while (current_state > QUIT)
    current_state = command_items[current_state].func(client);
    
  if (client->request[client->request_size - 1] != '\0') {
    printf("amagaaaad!\n");
    return FLEE;
  }
  printf("size efter process:\t%d\n", client->request_size);
  printf("size enligt strings:\t%d\n", string_size(client->request, CBUFF));
  printf("request canonical:\t%s\n", client->request);

  current_state = MAIN;
  return SUCC;
}