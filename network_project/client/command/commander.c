/*----------------------------------------------------------------------------------------------------------------COMMANDER
Menues being represented as instances of type 'menu_item' collected as list of 'items'. Each item stores constants relevant
for where the user is now and where she/he's heading next in the menu-system depending on input.

Yes indeed, this fell out WAY more MESSIER than I thought in andvance but it somewhat works quite nice. I think it's easier
to follow this bad boy from south to north, starting on the bottom with func 'command_driver'.                                                                                   
-------------------------------------------------------------------------------------------------------------------------*/
#include "stdlib.h"
#include "../system/scanner.h"
#include "../system/cstrings.h"
#include "commander.h"

typedef struct MenuItem {
  const uint8_t this_state;
  const uint8_t next_state;
  const char *cmnd;
} menu_item;

static menu_item main[] = {       //  Main Menu Items.
  {CMAIN, CMESG, "-comment"},
  {CMAIN, CDVCE, "-device"},
  {CMAIN, CHELP, "-help"},
  {CMAIN, CEXIT, "-exit"}
};

static menu_item mesg[] = {       //  Message Menu Items.
  {CMESG, CINIT, "-read"},
  {CMESG, CINIT, "-send"},
  {CMESG, CMAIN, "-back"}
};

static menu_item dvce[] = {       //  Device Menu Items.
  {CDVCE, CINIT, "-read"},
  {CDVCE, CDLED, "-push"},
  {CDVCE, CMAIN, "-back"}
};

static menu_item dled[] = {       //  Led (in device) Menu Items.
  {CDLED, CINIT, "-red"},
  {CDLED, CINIT, "-blue"},
  {CDLED, CINIT, "-green"},
  {CDLED, CMAIN, "-back"}
};

static menu_item help[] = {       //  Help Menu Item.
  {CHELP, CMAIN, "-back"},
};

static void protocol_reset(cmnd_t *command) {
/*Main Menu always resets the PROTOCOL.*/

  for (size_t i = 0; i < 3; i++)
    command->protocol[i] = 0x80;
  return;
}

static void protocol_write(cmnd_t *command, menu_item item, int8_t index) {
/*Set bits to PROTOCOL "on the fly".*/

  switch(item.this_state) {

  case CMAIN:
    protocol_reset(command);
    command->protocol[TBIDX] |= (1 << index);
  break;
  case CMESG:
    command->protocol[EBIDX] |= (index << RWBIT);
  break;
  case CDVCE:
    command->protocol[EBIDX] |= (index << RWBIT);
  break;
  case CDLED:
    command->protocol[ABIDX] |= (1 << index);
  break;
  case CHELP:
  break;
  default:
    System_Message("something went south while writing protocol.");
    exit(EXIT_FAILURE);
  }
  return;
}

static void print_options(menu_item *items, size_t size_array) {
/*Prints allowed commands in current item-menu.*/

  for (size_t i = 0; i < size_array; i++)
    System_Message(items[i].cmnd);
  return;
}

static int8_t command_scan(cmnd_t *command, menu_item *items, size_t size_array) {

  print_options(items, size_array);
  command->size_cmnd = scan_driver(command->cmnd, "select", SBUFF);

  for (size_t i = 0; i < size_array; i++) {
    if (string_comp(command->cmnd, items[i].cmnd, command->size_cmnd)) {
      if (i < size_array - 1)
        protocol_write(command, items[i], i);
      return items[i].next_state;
    }
  }
  System_Message("Not an option. Try again");
  return command->menu_state;
}

void command_driver(uint8_t *protocol) {

  cmnd_t command = {.menu_state = CMAIN,.protocol = protocol};

  while (command.menu_state != CINIT) {
   
    switch(command.menu_state) {
    case CMAIN:
      Render_Header("MAIN", "Select in menu by enter any of the available commands");
      command.menu_state = command_scan(&command, main, ARRAY_SIZE(main));
    break;
    case CMESG:
      Render_Header("COMMENT", "Read old comments or post a new");
      command.menu_state = command_scan(&command, mesg, ARRAY_SIZE(mesg));
    break;
    case CDVCE:
      Render_Header("DEVICE", "Read old LED-activity or interact yourself by enter '-push'");
      command.menu_state = command_scan(&command, dvce, ARRAY_SIZE(dvce));
    break;
    case CDLED:
      Render_Header("PUSH", "Choose colour");
      command.menu_state = command_scan(&command, dled, ARRAY_SIZE(dled));
    break;
    case CHELP:
      Render_Header("HELP", "Everything you need to know");
      command.menu_state = command_scan(&command, help, ARRAY_SIZE(help));
    break;
    } 
    if (command.menu_state == CEXIT)
      exit(EXIT_SUCCESS);
  }

  return;
}


/*------------------------------------------------------------------------------------------------------------Weird Example
Current 'menu_state' is CMAIN and client has entered "-comment". Hence bit 0 ("comment-business") will be set in 
Now, 'next_state' going to be CMESG where the user enters -read or -send wheras their index-positions tells if
the PROTOCOL's ECHO_BYTE going to have its RWBIT (read/write to database) set or cleared. Returns CINIT.
-------------------------------------------------------------------------------------------------------------------------*/

/*Every state has its own menu; 'items'. It and its size being fed into the 'command-scanner' where the allowed commands
 *being printed before the user choose one of them.
 
 *If there's a match - checked by 'string_comp' (SEE SYSTEM MODULE) - the instance (item) at index-pos (N) will be used
 *for assigning a bit mapped to the given command "on the fly" to the correct 'blueprint'-byte before returning the
 *instance's hard coded 'next_state' as upcoming -menu_state.
 
 *Recent/current menu_state will be reloaded if the user enters anything except allowed commands.*/


 /*Whithin the while-loop, the client's being thrown around in a "state-machine" where current 'menu_state' is assigned based
 *on command-choices. This party will carry on until 'menu_state' isn't CINIT (Command Init) or CEXIT (Command Exit).
 
 *If the client has rage quitted it means 'CEXIT' (Command Exit) and the program will terminate, oterwise it should end up
 *in a 'CINIT' (Command Init) wheras the blueprint being copied to the PROTOCOL.*/