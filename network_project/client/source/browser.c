/*----------------------------------------------------------------------------------------------------------------"BROWSER"
An "engine" of some sort during 'user-menu:ing' I came up with while playing around with function-pointers. Members of
'cmnd_item' guinding the user to the correct state depending on her/his commands. A neat caviat in this solution is how
bits being set (or cleared) simultaneously on the fly which finally being added to the request-protocol.
------------------------------------------------------------------------------------------------------------------------*/

#include "cstring.h"
#include "scanner.h"  
#include "browser.h"

static int8_t state = _MAIN;

/*-------------------------------------------------------------------------------------------------------COMMAND STRUCTURE
3 (for now, more to come) menues being represented as 'command item'. Each item stores constants relevant for where the
user are now and where she/he's heading depending on which command being typed.
/-----------------------------------------------------------------------------------------------------------------------*/
typedef struct CommandItem {
  const uint8_t this_state;
  const uint8_t next_state;
  const char *cmnd;
} cmnd_item;

static cmnd_item main[] = {
  {_MAIN, _MESG, "-message"},
  {_MAIN, _DVCE, "-device"},
  {_MAIN, _EXIT, "-exit"}
};

static cmnd_item mesg[] = {
  {_MESG, _INIT, "-read"},
  {_MESG, _INIT, "-send"},
  {_MESG, _MAIN, "-back"}
};

static cmnd_item dvce[] = {
  {_DVCE, _INIT, "-read"},
  {_DVCE, _DLED, "-init"},
  {_DVCE, _MAIN, "-back"}
};

static cmnd_item dled[] = {
  {_DLED, _INIT, "-red"},
  {_DLED, _INIT, "-blue"},
  {_DLED, _INIT, "-green"},
  {_DLED, _MAIN, "-back"}
};
/*---------------------------------------------------------------------------------------------------------BYTE BlUEPRINTS
The static variables TABLE, ATTRB and FORWD are used as blueprints during the command-session. Like the protocol-array
they being assigned to when the user's done they're unsigned bytes; this because not being regarded as nullbytes (which
screwed things up for me while sending package to the server).
/-----------------------------------------------------------------------------------------------------------------------*/
static uint8_t TABLE = 0x80;
static uint8_t ATTRB = 0x80;

static void reset_protocol(void) {
  TABLE = 0x80, ATTRB = 0x80;
  state = _MAIN;
}

static void write_protocol(cmnd_item item, int8_t index) {
/*'item' and 'index' args determines which state/item we're currently in and which index (command) the user choosed in the
 *'command_scan'-function prior. This data makes it possible for bitwise operation on the 'blueprint-bytes'
 */
  switch(item.this_state) {

  case _MAIN:
    reset_protocol();
    TABLE |= (1 << index);
  break;
  case _MESG:
    ATTRB |= (index << RWBIT);
  break;
  case _DVCE:
    ATTRB |= (index << RWBIT);
  break;
  case _DLED:
    ATTRB |= (1 << index);
  break;
  default:
    System_Message("Something went south while writing protocol.");
    exit(EXIT_FAILURE);
  }
  return;
}

static int8_t command_scan(cmnd_item *items, size_t size_array) {

  for (size_t i = 0; i < size_array; i++)
    printf("\t\t\t%s\n", items[i].cmnd);

  char command[SBUFF] = {'\0'};
  size_t cmnd_size = scan_driver(command, SBUFF, "select");

  for (size_t i = 0; i < size_array; i++) {
    if (string_comp(command, items[i].cmnd, cmnd_size)) {
      if (i < size_array - 1)
        write_protocol(items[i], i);
      return items[i].next_state;
    }
  }
  System_Message("Not an option. try again");
  return state;
}

int8_t browse_driver(uint8_t *protocol) {

  while (state != _INIT) {
   
    switch(state) {
    case _MAIN:
      Render_Header("MAIN       ", "Main ipsum dolor sit amet, consectetur adipiscing elit");
      state = command_scan(main, ARRAY_SIZE(main));
      break;
    case _MESG:
      Render_Header("MESSAGE    ", "Message ipsum dolor sit amet, consectetur adipiscing elit");
      state = command_scan(mesg, ARRAY_SIZE(mesg));
      break;
    case _DVCE:
      Render_Header("DEVICE     ", "Device ipsum dolor sit amet, consectetur adipiscing elit");
      state = command_scan(dvce, ARRAY_SIZE(dvce));
      break;
    case _DLED:
      Render_Header("INIT       ", "Ledinit ipsum dolor sit amet, consectetur adipiscing elit");
      state = command_scan(dled, ARRAY_SIZE(dled));
      break;
    }
    if (state == _EXIT) return EXIT;
  }

  protocol[TBYTE] = TABLE;
  protocol[ABYTE] = ATTRB;
  protocol[SBYTE] = ATTRB;

  return command_driver_check(protocol);
}
