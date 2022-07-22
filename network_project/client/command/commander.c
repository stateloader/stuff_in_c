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

static int8_t menu_state;

static uint8_t blueprint[3] = {
  0x80, 0x80, 0x80
};

static uint8_t TABLE = 0x80;
static uint8_t ATTRB = 0x80;
static uint8_t ECHOB = 0x80;

//The static variables TABLE, ATTRB and ECHOB are used as blueprints during the command-session, later attached to PROTOCOL.

static void protocol_reset(void) {
  TABLE = 0x80, ATTRB = 0x80, ECHOB = 0x80;
  return;
}

static void protocol_write(menu_item item, int8_t index) {
/*Set bits to PROTOCOL "on the fly". Guess the Exemple-comment below makes this mess easier to understand.*/

  switch(item.this_state) {
/*------------------------------------------------------------------------------------------------------------Weird Example
Current 'menu_state' is CMAIN and client has entered "-comment". Hence bit 0 ("comment-business") will be set in 
Now, 'next_state' going to be CMESG where the user enters -read or -send wheras their index-positions tells if
the PROTOCOL's ECHO_BYTE going to have its RWBIT (read/write to database) set or cleared. Returns CINIT.
-------------------------------------------------------------------------------------------------------------------------*/
  case CMAIN:
    protocol_reset();
    TABLE |= (1 << index);
  break;
  case CMESG:
    ECHOB |= (index << RWBIT);
  break;
  case CDVCE:
    ECHOB |= (index << RWBIT);
  break;
  case CDLED:
    ATTRB |= (1 << index);
  break;
  case CHELP:
    System_Message("just go nuts.");
  break;
  default:
    System_Message("something went south while writing protocol.");
    exit(EXIT_FAILURE);
  }
  return;
}

static void print_options(menu_item *items, size_t size_array) {
/*Prints allowed commands in (current) item-menu.*/
  for (size_t i = 0; i < size_array; i++)
    printf("\t\t\t%s\n", items[i].cmnd);
  return;
}

static int8_t command_scan(cmnd_t *command, menu_item *items, size_t size_array) {
  command->current = items;

  print_options(command->current, size_array);
  command->size_cmnd = scan_driver(command->cmnd, "select", SBUFF);


  for (size_t i = 0; i < size_array; i++) {
    if (string_comp(command->cmnd, items[i].cmnd, command->size_cmnd)) {
      if (i < size_array - 1)
        protocol_write(items[i], i);
      return items[i].next_state;
    }
  }
  System_Message("Not an option. try again");
  return menu_state;
}

void command_driver(uint8_t *protocol) {

  menu_state = CMAIN;
  cmnd_t command = {.menu_state = CMAIN};

  while (menu_state != CINIT) {
   
    switch(menu_state) {
    case CMAIN:
      Render_Header("MAIN", "Select in menu by enter any of the available commands");
      command.current = main;
      menu_state = command_scan(&command, main, ARRAY_SIZE(main));
    break;
    case CMESG:
      Render_Header("COMMENT", "Read old comments or post a new");
      menu_state = command_scan(&command, mesg, ARRAY_SIZE(mesg));
    break;
    case CDVCE:
      Render_Header("DEVICE", "Read old LED-activity or interact yourself by enter '-push'");
      menu_state = command_scan(&command, dvce, ARRAY_SIZE(dvce));
    break;
    case CDLED:
      Render_Header("PUSH", "Pick a colour");
      menu_state = command_scan(&command, dled, ARRAY_SIZE(dled));
    break;
    case CHELP:
      Render_Header("HELP", "Everything you need to know");
      menu_state = command_scan(&command, help, ARRAY_SIZE(help));
    break;
    } 
    if (menu_state == CEXIT)
      exit(EXIT_SUCCESS);
  }

  protocol[TBIDX] = TABLE;
  protocol[ABIDX] = ATTRB;
  protocol[EBIDX] = ECHOB;

  return;
}


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