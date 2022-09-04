/*----------------------------------------------------------------------------------------COMMANDER
This fell out WAY more MESSIER than I thought in andvance but it somewhat works quite nice. I've
written different explanations but they turn up even messier. I'll put something in place later and
probably sanitize this bad boy a bit. 
-------------------------------------------------------------------------------------------------*/

#include "stdlib.h"
#include "../jackIO/scanner.h"
#include "../jackIO/cstrings.h"
#include "commander.h"

typedef struct MenuItem {
  const uint8_t this_state;
  const uint8_t next_state;
  const char *cmnd;
} menu_item;

//Main Menu Items.
static menu_item main[] = {
  {CMAIN, CMESG, "-comment"},
  {CMAIN, CDVCE, "-device"},
  {CMAIN, CHELP, "-help"},
  {CMAIN, CEXIT, "-exit"}
};
//Message Menu Items.
static menu_item mesg[] = {
  {CMESG, CINIT, "-read"},
  {CMESG, CINIT, "-send"},
  {CMESG, CMAIN, "-back"}
};
//Device Menu Items.
static menu_item dvce[] = {
  {CDVCE, CINIT, "-read"},
  {CDVCE, CDLED, "-push"},
  {CDVCE, CMAIN, "-back"}
};
//Led (in device) Menu Items.
static menu_item dled[] = {
  {CDLED, CINIT, "-red"},
  {CDLED, CINIT, "-blue"},
  {CDLED, CINIT, "-green"},
  {CDLED, CMAIN, "-back"}
};
//Help Menu Item.
static menu_item help[] = {
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
    command->protocol[TINDX] |= (1 << index);
  break;
  case CMESG:
    command->protocol[CINDX] |= (index << PPREQ);
  break;
  case CDVCE:
    command->protocol[CINDX] |= (index << PPREQ);
  break;
  case CDLED:
    command->protocol[PINDX] |= (1 << index);
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

  for (size_t i = 0; i < size_array; i++)
    System_Message(items[i].cmnd);

  return;
}

static int8_t command_scan(cmnd_t *command, menu_item *items, size_t size_array) {

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

  cmnd_t command = {.menu_state = CMAIN,.protocol = protocol};

  while (command.menu_state != CINIT) {
   
    switch(command.menu_state) {
    case CMAIN:
      Render_Header("MAIN", "Select in menu by enter any of the available commands.");
      command.menu_state = command_scan(&command, main, ARRAY_SIZE(main));
    break;
    case CMESG:
      Render_Header("COMMENT", "Read old comments or post a new.");
      command.menu_state = command_scan(&command, mesg, ARRAY_SIZE(mesg));
    break;
    case CDVCE:
      Render_Header("DEVICE", "Read old LED-activity or interact yourself by enter \"-push\".");
      command.menu_state = command_scan(&command, dvce, ARRAY_SIZE(dvce));
    break;
    case CDLED:
      Render_Header("PUSH", "Choose colour.");
      command.menu_state = command_scan(&command, dled, ARRAY_SIZE(dled));
    break;
    case CHELP:
      Render_Header("HELP", "You're on your own for now.");
      command.menu_state = command_scan(&command, help, ARRAY_SIZE(help));
    break;
    case CEXIT:
      Render_Header("BYE!", "bye!");
      exit(EXIT_SUCCESS);
    break;
    }
  }
  return;
}
