/*----------------------------------------------------------------------------------------------------------------COMMANDER
Menues being represented as instances of type 'menu_item' collected as list of 'items'. Each menu stores constants relevant
for where the user is now and where she/he's heading next in the menu-system depending on input.

Yes indeed, this fell out WAY more MESSIER than I thought in andvance but it somewhat works quite nice. Guess it's easier
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
/*Set bits to PROTOCOL "on the fly". Every revisit to the Main Menu - state 'CMAIN' - will reset PROTOCOL to
 *default which means MSB set while rest of them is cleared.*/

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
/*Different 'menu_state's feed different 'items' into the function. Allowed commands stored among these items
 *will be printed before the user enter one of them. Their index-position determines which bit that will be set
 *inside 'protocol_write' and current state ('this_state') maps which byte its going to be.*/

  print_options(items, size_array);
  command->size_cmnd = scan_driver(ASCI_PLUG, 512, command->cmnd, "select");

  for (size_t i = 0; i < size_array; i++) {
    if (string_comp(command->size_cmnd, command->cmnd, items[i].cmnd)) {
      if (i < size_array - 1)
        protocol_write(command, items[i], i);
      return items[i].next_state;
    }
  }
  System_Message("Not an option. Try again");

  return command->menu_state;
}

void command_driver(uint8_t *protocol) {
/*Struct-variable 'command' assigns its member 'menu_state' to CMAIN while 'protocol' - pointer of type uint8_t -
 *points at <porotocol/byt namn>. Depending on input the user gives, 'menu_state' vill jump back and forth in the
 *switch-statement whithin the while-loop until the user rage quits or makes a decision. At this point, the protocol
 will become 'the' PROTOCOL.*/

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
    case CEXIT:
      Render_Header("BYE!", "asdasda asd asd aasd asd  sdd s.");
      exit(EXIT_SUCCESS);
    break;
    }
  }
  return;
}
